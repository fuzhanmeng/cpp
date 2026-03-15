#pragma once

#include <functional>

class EventLoop;

class Channel {
public:
    using EventCallback = std::function<void()>;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    // 严禁拷贝
    Channel(const Channel&) = delete;
    Channel& operator=(const Channel&) = delete;

    // 1. 核心事件分发接口 (供 EventLoop::Poller 触发)
    void HandleEvent();

    // 2. 回调注册接口 (供 TcpConnection / Acceptor 绑定逻辑)
    void SetReadCallback(const EventCallback& callback) { read_callback_ = callback; }
    void SetWriteCallback(const EventCallback& callback) { write_callback_ = callback; }
    void SetCloseCallback(const EventCallback& callback) { close_callback_ = callback; }
    void SetErrorCallback(const EventCallback& callback) { error_callback_ = callback; }

    // 3. 物理属性与内核事件状态
    int fd() const { return fd_; }
    int events() const { return events_; }
    void set_revents(int revents) { revents_ = revents; }

    // 4. 事件位掩码 (Bitmask) 操作接口
    void EnableRead() {
        events_ |= kReadEvent;
        Update();
    }
    void DisableRead() {
        events_ &= ~kReadEvent;
        Update();
    }

    void EnableWrite() {
        events_ |= kWriteEvent;
        Update();
    }
    void DisableWrite() {
        events_ &= ~kWriteEvent;
        Update();
    }

    void DisableAll() {
        events_ = kNoneEvent;
        Update();
    }

    // 状态查询
    bool IsWriting() const { return events_ & kWriteEvent; }
    bool IsReading() const { return events_ & kReadEvent; }
    bool IsNoneEvent() const { return events_ == kNoneEvent; }

private:
    // 将最新的 events_ 状态同步给内核的 Epoll
    void Update();

    // 平台相关的底层事件宏映射 (对应 sys/epoll.h)
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;
    int fd_;

    int events_; // 用户期望监听的事件 (User-interested events)
    int revents_; // 内核实际返回的就绪事件 (Ready events)

    EventCallback read_callback_;
    EventCallback write_callback_;
    EventCallback close_callback_;
    EventCallback error_callback_;
};