#pragma once

#include <memory>
#include <vector>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool {
public:
    // 构造时必须绑定主线程的 EventLoop
    explicit EventLoopThreadPool(EventLoop* base_loop);
    ~EventLoopThreadPool();

    EventLoopThreadPool(const EventLoopThreadPool&) = delete;
    EventLoopThreadPool& operator=(const EventLoopThreadPool&) = delete;

    // 设置底层 Sub Reactor 线程的数量
    void SetThreadNum(int num_threads) { num_threads_ = num_threads; }

    // 启动线程池，触发所有子线程的底层的 clone() 系统调用
    void Start();

    // 核心调度接口：使用 Round-Robin (轮询) 算法获取下一个 Sub Reactor
    EventLoop* GetNextLoop();

private:
    EventLoop* base_loop_; // 主线程的 EventLoop
    bool started_;         // 运行状态机标志位
    int num_threads_;      // 预设的线程池容量
    int next_;             // 轮询调度游标 (Round-Robin Index)

    // 物理线程对象的生命周期容器
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    
    // 子线程局部 EventLoop 指针的高速缓存数组，提升分发效率
    std::vector<EventLoop*> loops_;
};