#include "channel.h"

#include <sys/epoll.h>
#include <sys/socket.h>

#include <functional>
#include <iostream>

#include "event_loop.h"

Channel::Channel(EventLoop* loop, int fd) : loop_(loop), fd_(fd), listen_events_(0), ready_events_(0) {}

Channel::~Channel() {}

void Channel::SetReadCallback(std::function<void()> const& callback) { read_callback_ = callback; }

void Channel::HandleEvent() {
    // 🌟 加这一句：看看是不是位运算匹配失败了！
    std::cout << "[底层诊断] Channel 触发！所属 fd: " << fd_ << "，内核返回事件: " << ready_events_ << std::endl;

    if (ready_events_ & (EPOLLIN | EPOLLPRI)) {
        if (read_callback_) {
            read_callback_();
        } else {
            std::cout << "[底层诊断] 警告：该 Channel 肚子里的回调是空的！" << std::endl;
        }
    }
}
void Channel::EnableRead() {
    listen_events_ |= EPOLLIN; // 1. 自己做好标记：我要监听可读事件
    loop_->UpdateChannel(this); // 2. 极其关键：跑去告诉EventLoop，帮我把这个标记同步给内核的 Epoll！
}