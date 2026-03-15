#include "epoll.h"

#include <sys/epoll.h>
#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "channel.h"

constexpr int kInitEventsSize = 16;

Epoll::Epoll() {
    epoll_fd_ = ::epoll_create1(0);
    if (epoll_fd_ == -1) {
        std::cerr << "create epoll fd error" << std::endl;
        abort();
    }

    events_.resize(kInitEventsSize);
}

Epoll::~Epoll() {
    if (epoll_fd_ != -1) {
        ::close(epoll_fd_);
    }
}

void Epoll::UpdateChannel(Channel* channel) {
    int fd = channel->fd();
    struct epoll_event ev {};

    // 调用 events() 获取用户态期望监听的事件掩码
    ev.events = channel->events();
    ev.data.ptr = channel;

    // 调用 IsNoneEvent() 进行语义化判断
    if (channel->IsNoneEvent()) {
        if (::epoll_ctl(epoll_fd_, EPOLL_CTL_DEL, fd, &ev) < 0) {
            std::cerr << "[Epoll] epoll_ctl DEL 错误, FD: " << fd << std::endl;
        } else {
            std::cout << "[Epoll] 成功将 FD: " << fd << " 从 Epoll 树中移除" << std::endl;
        }
    } else {
        if (::epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, fd, &ev) < 0) {
            if (errno == ENOENT) {
                if (::epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, fd, &ev) < 0) {
                    std::cerr << "[Epoll] epoll_ctl ADD 致命错误" << std::endl;
                    abort();
                } else {
                    std::cout << "[Epoll] 成功挂载 FD: " << fd << "，监听掩码: " << ev.events << std::endl;
                }
            } else {
                std::cerr << "[Epoll] epoll_ctl MOD 致命错误" << std::endl;
            }
        }
    }
}

std::vector<Channel*> Epoll::Poll(int timeout) {
    int ready_nums = ::epoll_wait(epoll_fd_, events_.data(), static_cast<int>(events_.size()), timeout);

    if (ready_nums < 0) {
        if (errno == EINTR)
            return {};
        std::cerr << "[Epoll] epoll_wait 致命错误" << std::endl;
        abort();
    } else if (ready_nums == 0) {
        return {};
    }

    std::vector<Channel*> active_channels;
    active_channels.reserve(ready_nums);

    for (int i = 0; i < ready_nums; ++i) {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);

        // 调用 set_revents() 将内核返回的真实就绪事件写入 Channel
        channel->set_revents(static_cast<int>(events_[i].events));

        active_channels.emplace_back(channel);
    }

    // 动态扩容逻辑
    if (static_cast<size_t>(ready_nums) == events_.size()) {
        events_.resize(events_.size() * 2);
    }

    return active_channels;
}