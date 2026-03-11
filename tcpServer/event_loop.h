#pragma once

#include <memory>
#include <vector>

#include "channel.h"
#include "epoll.h"

class Epoll;
class Channel;

class EventLoop {
public:
    EventLoop();
    ~EventLoop();

    EventLoop(const EventLoop&) = delete;
    EventLoop& operator=(const EventLoop&) = delete;

    // 开启无限事件循环
    void Loop();

    // 安全退出的开关
    void Quit();

    // 当 Channel 的监听事件改变时，通过此函数向底层的 Epoll 同步
    void UpdateChannel(Channel* channel);

private:
    std::unique_ptr<Epoll> epoll_; // EventLoop 独占底层的 Epoll 封装类
    bool quit_; // 控制死循环的标志位
};