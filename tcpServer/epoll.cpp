#include "epoll.h"

#include <sys/epoll.h>
#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "channel.h"

constexpr int kEventsSize = 1024;

Epoll::Epoll() {
    epoll_fd_ = ::epoll_create1(0);
    if (epoll_fd_ == -1) {
        std::cerr << "create epoll fd error" << std::endl;
        abort();
    }

    events_.resize(kEventsSize);
}

Epoll::~Epoll() {
    if (epoll_fd_ != -1) {
        ::close(epoll_fd_);
    }
}

void Epoll::UpdateChannel(Channel* channel) {
    int fd = channel->fd();
    struct epoll_event ev {};
    ev.events = channel->listen_events();
    ev.data.ptr = channel;

    std::cout << "[底层诊断] Epoll 注册 fd: " << fd << "，监听事件掩码: " << ev.events << std::endl;
    // 聪明的防呆设计：我们不知道这个 Channel 是第一次来，还是来修改状态的。
    // 我们先尝试 MOD（修改），如果内核报错说 ENOENT（没找到这个 fd），我们就改成 ADD（新增）！

    if (::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &ev)) {
        if (errno == ENOENT) {
            if (::epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev)) {
                std::cerr << "epoll_ctl ADD error" << std::endl;
                abort();
            }
        }
    }
}

//
std::vector<Channel*> Epoll::Poll(int timeout) {
    int ready_nums = epoll_wait(epoll_fd_, events_.data(), static_cast<int>(events_.size()), timeout);

    if (ready_nums < 0) {
        if (errno == EINTR) {
            std::cout << "被信号打断，不算真错，返回一个空的 vector" << std::endl;
            return {};
        }
        std::cerr << "epoll_wait error" << std::endl;
        abort();
    } else if (ready_nums == 0) {
        // timeout 到了，但是没有事件
        return {};
    }

    std::vector<Channel*> active_channels;
    active_channels.reserve(ready_nums);
    for (int i = 0; i < ready_nums; ++i) {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);

        // 把实际发生的事件（比如 EPOLLIN）记录到 Channel 身上，方便它等会做判断
        channel->set_ready_events(events_[i].events);

        active_channels.emplace_back(channel);
    }

    return active_channels;
}
