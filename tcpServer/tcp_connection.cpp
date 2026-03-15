#include "tcp_connection.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>

#include "buffer.h"
#include "channel.h"
#include "event_loop.h"
#include "socket.h"

constexpr int kArraySize = 65536;

TcpConnection::TcpConnection(EventLoop* loop, int fd)
    : loop_(loop),
      sock_(std::make_unique<Socket>(fd)),
      channel_(std::make_unique<Channel>(loop, fd)),
      state_(kConnecting) {
    // 将本类的物理处理函数，注册给底层的 Channel 路由器
    channel_->SetReadCallback([this]() { this->HandleRead(); });
    channel_->SetWriteCallback([this]() { this->HandleWrite(); });

    // 状态机流转：标记为已连接
    set_state(kConnected);

    // 启动监听：向 Epoll 注册 EPOLLIN 事件
    channel_->EnableRead();

    std::cout << "[TcpConnection] 物理连接建立,FD: " << fd << "，状态机转入 kConnected,开始监听 EPOLLIN" << std::endl;
}

TcpConnection::~TcpConnection() {
    // 严谨的状态断言：只有在断开状态下才允许物理销毁
    if (state_ != kDisconnected) {
        std::cerr << "[TcpConnection] 警告:在未完全断开连接的情况下触发析构!FD: " << fd() << std::endl;
    }
    std::cout << "[TcpConnection] 资源物理销毁完毕,FD: " << fd() << std::endl;
    // sock_ 和 channel_ 会随着 unique_ptr 自动释放，sock_ 的析构会自动 close(fd)
}

void TcpConnection::SetMessageCallback(const MessageCallback& callback) { message_callback_ = callback; }

void TcpConnection::SetCloseCallback(const CloseCallback& callback) { close_callback_ = callback; }

void TcpConnection::SetWriteCompleteCallback(const WriteCompleteCallback& callback) {
    write_complete_callback_ = callback;
}

int TcpConnection::fd() const { return sock_->fd(); }

void TcpConnection::HandleRead() {
    if (state_ != kConnected && state_ != kDisconnecting) {
        return;
    }

    // 栈上分配 64KB 临时接收缓冲区，零堆分配开销
    std::array<char, kArraySize> extrabuf{};

    // 专业细节：这里其实不需要减 1。因为你的 Buffer 是二进制安全的（通过长度截断），
    // 不需要像 C 语言的 strcpy 那样强行预留一个 '\0' 的位置。直接用 size() 即可压榨满容量。
    ssize_t bytes_recv = ::recv(sock_->fd(), extrabuf.data(), extrabuf.size(), 0);

    if (bytes_recv > 0) {
        input_buffer_.Append(extrabuf.data(), bytes_recv);

        // 2. 触发应用层回调，交出 Buffer 的控制权
        if (message_callback_) {
            message_callback_(this, &input_buffer_);
        }
    } else if (bytes_recv == 0) {
        // 对端正常关闭连接 (发送了 FIN 报文)
        HandleClose();
    } else {
        // 非阻塞 I/O 的异常处理
        // EAGAIN / EWOULDBLOCK 表示当前内核缓冲区已被读空，这是正常的非阻塞返回，无需报错
        if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
            std::cerr << "[TcpConnection] HandleRead 底层 ::recv 发生致命错误: " << strerror(errno)
                      << " (errno=" << errno << ")" << std::endl;
            HandleError();
        }
    }
}

void TcpConnection::HandleClose() {
    // 状态机流转：防止重复关闭
    if (state_ == kDisconnected)
        return;

    set_state(kDisconnected);
    std::cout << "[TcpConnection] 处理连接关闭逻辑，FD: " << fd() << std::endl;

    // 物理注销：从 Epoll 中移除所有监听事件 (EPOLLIN / EPOLLOUT)
    // 防止底层套接字在析构期间依然被内核唤醒，导致野指针崩溃
    channel_->DisableAll();

    // 向上层呼救：通知 TcpServer 在哈希表中 erase 掉自己,执行完这一步，本对象的 unique_ptr 将被销毁，触发析构函数
    if (close_callback_) {
        close_callback_(this);
    }
}

void TcpConnection::HandleError() {
    int err = 0;
    socklen_t optlen = sizeof(err);
    // 通过 getsockopt 提取内核中该套接字暂存的真实错误码
    if (::getsockopt(sock_->fd(), SOL_SOCKET, SO_ERROR, &err, &optlen) < 0) {
        err = errno;
    }

    std::cerr << "[TcpConnection] 捕获到底层套接字 SO_ERROR: " << strerror(err) << " (err=" << err << "),FD: " << fd()
              << std::endl;

    // 错误发生后，唯一的正确做法就是强制清理资源并断开连接
    HandleClose();
}

void TcpConnection::Send(const std::string& msg) {
    if (state_ != kConnected) {
        std::cerr << "[TcpConnection] 警告:连接已断开,放弃发送数据,FD: " << fd() << std::endl;
        return;
    }

    // Number written ,本次成功写入内核的字节数
    ssize_t nwrote = 0;
    // 剩余待处理的字节数
    size_t remaining = msg.size();
    // 致命系统错误标志位
    bool fault_error = false;

    // 1. 极致优化：如果当前 output_buffer_ 是空的，并且没有注册 EPOLLOUT 事件，
    // 说明此时内核发送通道非常通畅，我们直接尝试绕过 Buffer，直接调用系统 API 发送。
    if (!channel_->IsWriting() && output_buffer_.ReadableBytes() == 0) {
        nwrote = ::send(sock_->fd(), msg.data(), msg.size(), 0);
        if (nwrote > 0) {
            remaining -= nwrote;
            // 如果一次性全部发完了，直接触发写完成回调
            if (remaining == 0 && write_complete_callback_) {
                write_complete_callback_(this);
            }
        } else {
            nwrote = 0;
            // 非阻塞正常的拥塞返回
            if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
                std::cerr << "[TcpConnection] Send 直接发送时发生底层致命错误" << std::endl;
                if (errno == EPIPE || errno == ECONNRESET) {
                    fault_error = true;
                }
            }
        }
    }
    // 2. 异步缓存与事件注册：
    // 如果刚才没发完（或者根本没尝试发），必须将剩余的数据追加到 output_buffer_ 中
    if (!fault_error && remaining > 0) {
        output_buffer_.Append(msg.data() + nwrote, remaining);

        // 只要 output_buffer_ 里还有积压数据，就必须向 Epoll 注册 EPOLLOUT 事件，让内核在缓冲区有空位时通知我们
        if (!channel_->IsWriting()) {
            channel_->EnableWrite();
        }
    }
}

void TcpConnection::HandleWrite() {
    // 这个函数由底层的 Epoll 在触发 EPOLLOUT 事件时调用
    if (channel_->IsWriting()) {
        // 尝试将 output_buffer_ 中的所有有效数据，一次性灌入内核
        ssize_t n = ::send(sock_->fd(), output_buffer_.Peek(), output_buffer_.ReadableBytes(), 0);

        if (n > 0) {
            // 物理发送成功，推进 Buffer 的读游标，相当于“吃掉/丢弃”已经发送成功的数据
            output_buffer_.Retrieve(n);

            // 如果 output_buffer_ 已经被彻底发空了
            if (output_buffer_.ReadableBytes() == 0) {
                // 必须立即注销 EPOLLOUT 事件！否则会引发 Epoll 的 Busy Loop (CPU 100% 空转)
                channel_->DisableWrite();

                // 触发高水位回调，通知业务层可以继续塞大文件了
                if (write_complete_callback_) {
                    write_complete_callback_(this);
                }

                // 如果业务层之前调用了 Shutdown，现在积压的数据终于发完了，正式执行底层的断开操作
                if (state_ == kDisconnected) {
                    Shutdown();
                }
            }
        } else {
            std::cerr << "[TcpConnection] HandleWrite 时 ::send 发生系统错误" << std::endl;
        }
    } else {
        std::cerr << "[TcpConnection] 警告：没有注册写事件，却触发了 HandleWrite,FD: " << fd() << std::endl;
    }
}

void TcpConnection::Shutdown() {
    // 将状态切换为正在断开，阻止业务层继续调用 Send
    if (state_ == kConnected) {
        set_state(kDisconnecting);
    }

    // TCP 半关闭策略 (Half-Close)：
    // 只有当 output_buffer_ 里的数据已经被全物理清空时，才真正去关闭底层的写端。
    // 如果 IsWriting() 为 true，说明还有数据在排队，由 HandleWrite 负责在发完后再次调用本函数
    if (!channel_->IsWriting()) {
        std::cout << "[TcpConnection] 执行 TCP 半关闭 (SHUT_WR),FD: " << fd() << std::endl;

        // SHUT_WR：关闭写通道,内核会将缓冲区残留数据发往对端，并发送 FIN 报文
        // 但是读通道依然打开，依然可以接收对端发来的最后遗言，直到对端也发送 FIN (触发 HandleClose)
        if (::shutdown(sock_->fd(), SHUT_WR) < 0) {
            std::cerr << "[TcpConnection] ::shutdown 错误" << std::endl;
        }
    }
}