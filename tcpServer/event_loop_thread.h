#pragma once

#include <condition_variable>
#include <mutex>
#include <thread>

class EventLoop;

class EventLoopThread {
public:
    EventLoopThread();
    ~EventLoopThread();

    // 严禁拷贝：物理线程对象不可被复制
    EventLoopThread(const EventLoopThread&) = delete;
    EventLoopThread& operator=(const EventLoopThread&) = delete;

    // 启动底层 OS 线程，并安全返回内部 EventLoop 的指针
    EventLoop* StartLoop();

private:
    // 物理线程实际执行的入口函数
    void ThreadFunc();

    EventLoop* loop_; // 指向子线程局部 EventLoop 的指针
    bool exiting_; // 线程退出标志

    std::thread thread_; // 底层的 C++ 线程对象
    std::mutex mutex_; // 用于保护 loop_ 指针初始化的互斥锁
    std::condition_variable cond_; // 用于主从线程握手的条件变量
};