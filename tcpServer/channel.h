#pragma once

#include <cstdint>
#include <functional>

class EventLoop;

class Channel {
public:
    // 构造函数：一个 Channel 必须绑定一个 EventLoop 和一个 fd
    Channel(EventLoop* loop, int fd);
    ~Channel();

    Channel(const Channel&) = delete;
    Channel& operator=(const Channel&) = delete;

    void SetReadCallback(std::function<void()> const& callback);

    // 当 Epoll 发现这个 fd 有动静时，EventLoop 会调用这个函数
    void HandleEvent();

    // 告诉底层的 Epoll，开始监听这个 fd 的可读事件
    void EnableRead();

    int fd() const { return fd_; }

    // 返回正在监听的事件（交由 Epoll 注册用）
    uint32_t listen_events() const { return listen_events_; }

    // Epoll 触发时，把实际发生的事件（比如 EPOLLIN）写进来
    uint32_t ready_events() const { return ready_events_; }
    void set_ready_events(uint32_t ev) { ready_events_ = ev; }

private:
    EventLoop* loop_; // 这个 Channel 归哪个大管家（EventLoop）管
    int fd_; // 这个 Channel 绑定的底层文件描述符

    uint32_t listen_events_; // 我们期望 Epoll 监听的事件（比如 EPOLLIN）
    uint32_t ready_events_; // Epoll 实际返回给我们的活跃事件

    // 🌟 处理预案：存放上层传进来的可读回调函数
    std::function<void()> read_callback_;
};