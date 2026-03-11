#pragma once

#include <sys/epoll.h>

#include <cstdint>
#include <vector>

#include "channel.h"
class Channel;
class Epoll {
public:
    Epoll();
    ~Epoll();

    Epoll(const Epoll&) = delete;
    Epoll& operator=(const Epoll&) = delete;

    void UpdateChannel(Channel* channel);
    std::vector<Channel*> Poll(int timeout = -1);

private:
    int epoll_fd_;
    std::vector<struct epoll_event> events_;
};