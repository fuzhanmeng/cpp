#include "event_loop_thread.h"

#include "event_loop.h"

EventLoopThread::EventLoopThread() : loop_(nullptr), exiting_(false) {}

EventLoopThread::~EventLoopThread() {
    exiting_ = true;
    if (loop_ != nullptr) {
        // 1. 触发子线程的 eventfd 唤醒，并使其退出 epoll_wait 循环
        loop_->Quit();
        // 2. 阻塞主线程，等待子线程物理执行结束，回收内核资源
        thread_.join();
    }
}

EventLoop* EventLoopThread::StartLoop() {
    // 1. 发起底层的 clone() 系统调用创建并启动子线程,子线程将立刻开始执行 ThreadFunc 函数
    thread_ = std::thread(&EventLoopThread::ThreadFunc, this);

    EventLoop* loop = nullptr;
    {
        // 2. 主线程在此处加锁，并陷入条件变量的挂起状态 (Wait)
        // 必须死死等住，直到子线程在它的栈上把 EventLoop 真正创建出来！
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this]() { return loop_ != nullptr; });
        loop = loop_;
    }

    // 3. 握手成功，主线程安全拿到子线程 EventLoop 的指针并返回
    return loop;
}

void EventLoopThread::ThreadFunc() {
    // 1. 在当前子线程的物理栈帧 (Stack Frame) 上创建一个完全独立的 EventLoop。
    EventLoop loop;

    {
        // 2. 获取互斥锁，将局部对象的地址赋给成员变量
        std::lock_guard<std::mutex> lock(mutex_);
        loop_ = &loop;

        // 3. 唤醒正挂起在 condition_variable 上的主线程
        cond_.notify_one();
    }

    // 4. 开始底层 Epoll 的无限阻塞轮询,除非外部调用了 loop_->Quit()，否则该线程将永远停留在这一行
    loop.Loop();

    // 5. 循环结束，线程即将消亡，安全清空指针
    std::lock_guard<std::mutex> lock(mutex_);
    loop_ = nullptr;
}