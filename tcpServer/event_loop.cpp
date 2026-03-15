#include "event_loop.h"

#include <sys/eventfd.h>
#include <unistd.h>

#include <iostream>

#include "channel.h"
#include "epoll.h"

// 辅助函数：创建一个非阻塞的 eventfd 用于唤醒
int CreateEventFd() {
    // EFD_NONBLOCK: 非阻塞, EFD_CLOEXEC: 防止子进程继承
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0) {
        std::cerr << "[EventLoop] 致命错误：无法创建 wakeup eventfd" << std::endl;
        abort();
    }
    return evtfd;
}

EventLoop::EventLoop()
    : epoll_(std::make_unique<Epoll>()),
      quit_(false),
      wakeup_fd_(CreateEventFd()), // 1. 创建唤醒 FD
      wakeup_channel_(std::make_unique<Channel>(this, wakeup_fd_)) { // 2. 用 Channel 包装它

    std::cout << "[EventLoop] 构造完成，底层 Epoll 初始化，Wakeup FD: " << wakeup_fd_ << std::endl;

    // 🌟 核心绑定：当 wakeup_fd_ 收到数据可读时，触发 HandleWakeup
    wakeup_channel_->SetReadCallback([this]() { this->HandleWakeup(); });
    // 将唤醒通道注册到 Epoll 中，永远监听可读事件
    wakeup_channel_->EnableRead();
}

EventLoop::~EventLoop() {
    // 关闭唤醒描述符
    ::close(wakeup_fd_);
    std::cout << "[EventLoop] 析构销毁" << std::endl;
}

void EventLoop::Loop() {
    quit_ = false;
    std::cout << "[EventLoop] Loop 启动，开始事件轮询..." << std::endl;

    while (!quit_) {
        // 1. 阻塞等待底层 Epoll 返回就绪的事件 (包括网络 IO 和 Wakeup 唤醒)
        std::vector<Channel*> active_channels = epoll_->Poll();

        // 2. 将就绪事件分发给对应的 Channel 去处理
        for (auto* channel : active_channels) {
            channel->HandleEvent();
        }

        // 🌟 3. 核心调度：网络 IO 处理完毕后，集中处理积压的异步任务！
        // 因为上一步的 HandleEvent 可能触发了连接断开，从而向队列塞入了“销毁”任务。
        // 在这里统一执行，绝对安全，彻底避开野指针陷阱 (UAF)！
        DoPendingFunctors();
    }

    std::cout << "[EventLoop] Loop 停止运行" << std::endl;
}

void EventLoop::Quit() {
    quit_ = true;
    // 无论从哪个线程调用 Quit，都强行唤醒底层的 epoll_wait
    Wakeup();
}

void EventLoop::UpdateChannel(Channel* channel) { epoll_->UpdateChannel(channel); }

// ---------------------------------------------------------
// 异步唤醒与任务调度机制
// ---------------------------------------------------------

void EventLoop::QueueInLoop(Functor cb) {
    {
        // 加锁，保护 vector
        std::lock_guard<std::mutex> lock(mutex_);
        pending_functors_.push_back(std::move(cb));
    }
    // 塞入任务后，为了让 EventLoop 尽快执行它，强行唤醒 Epoll
    Wakeup();
}

void EventLoop::Wakeup() {
    uint64_t one = 1;
    // 往 eventfd 里写入 8 个字节，底层的 epoll_wait 会立刻收到可读事件而被唤醒
    ssize_t n = ::write(wakeup_fd_, &one, sizeof(one));
    if (n != sizeof(one)) {
        std::cerr << "[EventLoop] Wakeup 写入错误" << std::endl;
    }
}

void EventLoop::HandleWakeup() {
    uint64_t one = 1;
    // 把 Wakeup 写入的数据读出来，清空缓冲，避免 Epoll 一直被触发 (LT模式)
    ssize_t n = ::read(wakeup_fd_, &one, sizeof(one));
    if (n != sizeof(one)) {
        std::cerr << "[EventLoop] HandleWakeup 读取错误" << std::endl;
    }
}

void EventLoop::DoPendingFunctors() {
    std::vector<Functor> functors;
    {
        // 交换局部变量与成员变量,不需要在执行任务时一直占着锁，防止阻塞其他想要塞任务的线程
        std::lock_guard<std::mutex> lock(mutex_);
        functors.swap(pending_functors_);
    }

    // 在无锁状态下，安全地执行所有积压的任务
    for (const auto& functor : functors) {
        functor();
    }
}