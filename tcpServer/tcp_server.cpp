#include "tcp_server.h"

#include <iostream>

#include "acceptor.h"
#include "event_loop.h"
#include "event_loop_thread_pool.h"
#include "tcp_connection.h"

TcpServer::TcpServer(EventLoop* loop, int port)
    : loop_(loop),
      acceptor_(std::make_unique<Acceptor>(loop, port)),
      thread_pool_(std::make_unique<EventLoopThreadPool>(loop)) { // 实例化线程池
    // 将 TcpServer 的私有方法，注册给底层的 Acceptor
    // 当 Acceptor 成功执行 accept() 后，会将新产生的 fd 传给 HandleNewConnection
    acceptor_->SetNewConnectionCallback([this](int new_client_fd) { this->HandleNewConnection(new_client_fd); });
}

TcpServer::~TcpServer() { std::cout << "[TcpServer] 正在销毁，触发 RAII 级联释放所有活动连接..." << std::endl; }

void TcpServer::SetThreadNum(int num_threads) {
    // 将线程数配置透传给底层的物理线程池
    thread_pool_->SetThreadNum(num_threads);
}

void TcpServer::Start() {
    // 触发底层的 clone() 系统调用，唤醒所有 Sub Reactor 线程
    thread_pool_->Start();
    std::cout << "[TcpServer] 服务已正式启动,Main Reactor 进入事件分发就绪状态。" << std::endl;
}

void TcpServer::SetMessageCallback(const MessageCallback& callback) { message_callback_ = callback; }

void TcpServer::HandleNewConnection(int new_client_fd) {
    std::cout << "[TcpServer] 捕获新连接 FD: " << new_client_fd << "，准备分配资源" << std::endl;
    // 1. 通过 Round-Robin 算法，从线程池获取一个极其空闲的 Sub Reactor
    EventLoop* io_loop = thread_pool_->GetNextLoop();

    std::cout << "[TcpServer] 捕获新连接 FD: " << new_client_fd << "，已将其物理绑定至 Sub Reactor 线程" << std::endl;

    // 2. 创建一个新连接的对象
    auto conn = std::make_unique<TcpConnection>(io_loop, new_client_fd);

    // 3. 把用户在 main 函数里注册给 TcpServer 的业务代码，原封不动地“透传”给底层的连接对象
    conn->SetMessageCallback(message_callback_);

    // 4. 当底层 recv 返回 0 时，TcpConnection 会调用此函数向 TcpServer 呼救
    conn->SetCloseCallback([this](TcpConnection* connection) { this->HandleCloseConnection(connection); });

    // 5. 移交控制权：这里依然在主线程执行，保证了 connections_ 字典的线程安全性
    connections_[new_client_fd] = std::move(conn);

    std::cout << "[TcpServer] 连接创建完毕，当前活跃连接数: " << connections_.size() << std::endl;
}

void TcpServer::HandleCloseConnection(TcpConnection* conn) {
    std::cout << "[TcpServer] 收到断开通知，准备清理 FD: " << conn->fd() << " 的资源" << std::endl;

    // 异步延迟销毁
    loop_->QueueInLoop([this, conn]() {
        this->connections_.erase(conn->fd());
        std::cout << "[TcpServer] 异步资源清理完毕，当前活跃连接数: " << this->connections_.size() << std::endl;
    });
}