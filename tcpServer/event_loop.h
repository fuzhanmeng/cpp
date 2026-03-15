#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <vector>

// 前向声明
class Epoll;
class Channel;

class EventLoop {
public:
    // 定义可以在 EventLoop 中执行的回调任务类型
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    EventLoop(const EventLoop&) = delete;
    EventLoop& operator=(const EventLoop&) = delete;

    void Loop();
    void Quit();
    void UpdateChannel(Channel* channel);

    // 将任务塞入队列，并在必要时唤醒 EventLoop 去执行
    void QueueInLoop(Functor callback);

private:
    // 唤醒相关的底层物理动作
    void HandleWakeup();
    void Wakeup();

    // 统一执行积压的异步任务
    void DoPendingFunctors();

    std::unique_ptr<Epoll> epoll_;
    bool quit_;

    // 异步唤醒机制 (Wakeup FD)
    int wakeup_fd_;
    std::unique_ptr<Channel> wakeup_channel_; // 包装 wakeup_fd_，让它也能被 Epoll 监听

    // 异步任务队列与锁
    std::mutex mutex_;
    std::vector<Functor> pending_functors_;
};