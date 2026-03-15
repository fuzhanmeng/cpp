#pragma once

#include <functional>
#include <memory>
#include <string>

#include "buffer.h"

class EventLoop;
class Socket;
class Channel;

class TcpConnection {
public:
    // 消息到达回调：当底层 epoll 触发可读事件，且数据被完整读入 input_buffer_ 后触发
    // 业务层通过操作 Buffer* 来进行应用层协议的解包（拆解粘包/半包）
    using MessageCallback = std::function<void(TcpConnection*, Buffer*)>;

    // 连接关闭回调：当对端发送 FIN 报文（recv 返回 0），或发生底层网络错误时触发。
    // 主要用于通知拥有此连接的 TcpServer 将其从哈希表中安全移除（erase）
    using CloseCallback = std::function<void(TcpConnection*)>;

    // 写完成回调：当output_buffer_中的数据被彻底排空（全部写入内核 TCP 发送缓冲区）时触发
    // 在发送大文件或连续大吞吐量数据时极其关键，业务层借此得知可以继续调用 Send 写入下一块数据，避免引发应用层 OOM
    using WriteCompleteCallback = std::function<void(TcpConnection*)>;

    // 维护用户态的 TCP 连接状态，防止在错误的状态下执行非法操作（如断开后依然调用 Send）
    enum StateE {
        kDisconnected, // 已断开
        kConnecting, // 正在连接
        kConnected, // 已连接
        kDisconnecting // 正在断开（调用了 Shutdown，但 output_buffer_ 中还有数据未发送完，处于半关闭状态）
    };

    // 构造函数：接管由 Acceptor 产生的已连接套接字 (Connected Socket FD)
    TcpConnection(EventLoop* loop, int fd);
    ~TcpConnection();

    // 严禁拷贝与移动：
    // TcpConnection 独占底层的 Socket FD 和 Channel 资源（RAII 语义）。
    // 拷贝会导致多个对象对同一个 FD 执行 close()，引发严重的 Double-Free 漏洞。
    TcpConnection(const TcpConnection&) = delete;
    TcpConnection& operator=(const TcpConnection&) = delete;

    void SetMessageCallback(const MessageCallback& callback);
    void SetCloseCallback(const CloseCallback& callback);
    void SetWriteCompleteCallback(const WriteCompleteCallback& cb);

    // 获取底层文件描述符，常用于日志追踪或作为 Hash Map 的 Key
    int fd() const;

    // 状态查询接口。
    bool IsConnected() const { return state_ == kConnected; }

    // 异步非阻塞发送数据：
    // 如果当前内核 TCP 发送窗口有空间，直接调用系统 API (send) 写入内核；
    // 如果内核空间不足（网络拥塞），将剩余数据追加到 output_buffer_，并向 epoll 注册 EPOLLOUT 事件，由底层接管后续发送
    void Send(const std::string& msg);

    // 优雅关闭 (Graceful Shutdown) 机制：
    // 不会立刻直接 close(fd),如果 output_buffer_ 中还有积压数据，会将状态置为 kDisconnecting
    // 等到底层 HandleWrite 将数据全部发送完毕后，再调用系统的 ::shutdown(fd, SHUT_WR) 关闭写端（TCP 半关闭）
    void Shutdown();

private:
    // 内部状态机切换逻辑
    void set_state(StateE state) { state_ = state; }

    // 处理可读事件 (EPOLLIN)：调用 ::recv/readv 将网卡数据搬运至 input_buffer_，并触发 MessageCallback
    void HandleRead();

    // 处理可写事件 (EPOLLOUT)：调用 ::send 将 output_buffer_ 中的积压数据刷入内核。全部刷完则注销 EPOLLOUT 并触发
    // WriteCompleteCallback
    void HandleWrite();

    // 处理关闭事件 (EPOLLHUP 或 recv 返回 0)：执行资源清理流程，并触发 CloseCallback 通知 TcpServer 销毁本对象
    void HandleClose();

    // 处理异常事件 (EPOLLERR)：通过 getsockopt(SO_ERROR) 获取底层错误码，记录错误日志，并转入 HandleClose 逻辑
    void HandleError();

    EventLoop* loop_; // 当前连接所属的 Reactor 事件循环（Reactor 线程）
    std::unique_ptr<Socket> sock_; // 封装底层通信 FD，负责其生命周期管理 (RAII)
    std::unique_ptr<Channel> channel_; // 封装 FD 的事件分发机制，与 Epoll 交互

    // 回调函数存储
    MessageCallback message_callback_;
    CloseCallback close_callback_;
    WriteCompleteCallback write_complete_callback_;

    StateE state_; // 连接的当前逻辑状态

    Buffer input_buffer_; // 接收缓冲区：平滑网络接收字节流，供业务层进行协议解析，彻底解决粘包/半包问题。
    Buffer output_buffer_; // 发送缓冲区：缓存因内核发送窗口满而无法立即发出的数据，避免写阻塞导致的线程挂起。
};