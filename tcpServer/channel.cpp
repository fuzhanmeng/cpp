#include "channel.h"

#include <sys/epoll.h>
#include <sys/socket.h>

#include <functional>

#include "event_loop.h"

// 静态常量定义：映射底层的 epoll 宏
constexpr int Channel::kNoneEvent = 0;
// EPOLLPRI 表示有带外数据 (Out-of-band data) 到达，通常与 EPOLLIN 一同处理
constexpr int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
constexpr int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop, int fd) : loop_(loop), fd_(fd), events_(0), revents_(0) {}

Channel::~Channel() {}

void Channel::HandleEvent() {
    // 1. 处理底层套接字错误 (EPOLLERR)
    if (revents_ & EPOLLERR) {
        if (error_callback_)
            error_callback_();
    }

    // 2. 处理对端挂断 (EPOLLHUP)
    // 注意：当对端正常关闭并且没有数据可读时，才会触发挂断逻辑。
    // 如果有数据未读完 (EPOLLIN)，我们必须先去触发 ReadCallback 把残余数据读出来。
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        if (close_callback_)
            close_callback_();
    }

    // 3. 处理可读事件 (EPOLLIN / EPOLLPRI / EPOLLRDHUP)
    // EPOLLRDHUP: 对端关闭了写操作 (TCP 半关闭)，此时也应该触发读，让 recv 去返回 0
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
        if (read_callback_)
            read_callback_();
    }

    // 4. 处理可写事件 (EPOLLOUT)
    if (revents_ & EPOLLOUT) {
        if (write_callback_)
            write_callback_();
    }
}

// ---------------------------------------------------------
// 状态同步触发器
// ---------------------------------------------------------
void Channel::Update() {
    // Channel 本身不直接调用 epoll_ctl
    // 它通过所绑定的 EventLoop，将自身最新的 events_ 状态同步给底层的 Epoll 引擎
    // this 就是指向当前正在执行这段代码的 Channel 对象本身的指针
    loop_->UpdateChannel(this);
}