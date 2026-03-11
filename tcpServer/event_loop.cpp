#include "event_loop.h"

#include <iostream>
#include <memory>
#include <vector>

#include "channel.h"
#include "epoll.h"

EventLoop::EventLoop() : epoll_(std::make_unique<Epoll>()), quit_(false) {}

EventLoop::~EventLoop() {}

void EventLoop::Loop() {
    quit_ = false;

    std::cout << "EventLoop statr" << std::endl;
    while (!quit_) {
        std::vector<Channel*> active_channels = epoll_->Poll();

        for (auto* channel : active_channels) {
            channel->HandleEvent();
        }
    }

    std::cout << "EventLoop stop" << std::endl;
}

void EventLoop::Quit() { quit_ = true; }

void EventLoop::UpdateChannel(Channel* channel) { epoll_->UpdateChannel(channel); }
