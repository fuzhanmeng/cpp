#include "event_loop_thread_pool.h"

#include <iostream>

#include "event_loop.h"
#include "event_loop_thread.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* base_loop)
    : base_loop_(base_loop), 
      started_(false), 
      num_threads_(0), 
      next_(0) {}

EventLoopThreadPool::~EventLoopThreadPool() {
    // 由于使用了 std::unique_ptr，这里的 RAII 机制会自动析构 vector 中的 EventLoopThread 对象
    // 进而触发子线程的 Quit() 和 join() 物理回收动作
    std::cout << "[EventLoopThreadPool] 正在销毁线程池，释放底层资源..." << std::endl;
}

void EventLoopThreadPool::Start() {
    started_ = true;

    // 1. 预分配容器容量，防止动态扩容导致的内存拷贝
    threads_.reserve(num_threads_);
    loops_.reserve(num_threads_);

    // 2. 批量实例化并启动物理线程
    for (int i = 0; i < num_threads_; ++i) {
        auto t = std::make_unique<EventLoopThread>();
        
        // 阻塞等待子线程启动完毕，并安全获取其局部 EventLoop 的指针
        loops_.push_back(t->StartLoop());
        
        // 将物理线程对象移交容器管理
        threads_.push_back(std::move(t));
    }

    if (num_threads_ == 0) {
        // 降级机制：如果线程数为 0，退化为单线程 Reactor 模型
        // 所有的业务和 I/O 全部回退到主线程的 base_loop_ 中执行
        std::cout << "[EventLoopThreadPool] 线程池容量为 0,回退至单线程 Reactor 模式" << std::endl;
    } else {
        std::cout << "[EventLoopThreadPool] 成功启动 " << num_threads_ << " 个 Sub Reactor 线程" << std::endl;
    }
}

EventLoop* EventLoopThreadPool::GetNextLoop() {
    // 默认回退机制：如果没有启动子线程，直接返回主线程的 EventLoop
    EventLoop* loop = base_loop_;

    if (!loops_.empty()) {
        // 轮询
        loop = loops_[next_];
        ++next_;
        // 游标越界重置，形成物理闭环
        if (static_cast<size_t>(next_) >= loops_.size()) {
            next_ = 0;
        }
    }

    return loop;
}