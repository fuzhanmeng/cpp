#include "acceptor.h"

#include <netinet/in.h>
#include <sys/socket.h>

#include <iostream>
#include <memory>

#include "channel.h"
#include "event_loop.h"
#include "socket.h"

Acceptor::Acceptor(EventLoop* loop, int port)
    : loop_(loop),
      server_sock_(std::make_unique<Socket>()),
      accept_channel_(std::make_unique<Channel>(loop_, server_sock_->fd())) {
    // 1. 初始化底层 Listening Socket 配置
    server_sock_->BindAddress(port);
    server_sock_->Listen();
    server_sock_->SetNonBlocking();

    // 2. 将内部的 AcceptConnection 方法绑定为 Channel 的读事件回调
    accept_channel_->SetReadCallback([this]() { this->AcceptConnection(); });

    // 3. 向底层的 Epoll 实例注册 EPOLLIN 事件
    accept_channel_->EnableRead();
}

Acceptor::~Acceptor() {}

void Acceptor::SetNewConnectionCallback(const NewConnectionCallback& callback) {
    // 将回调函数保存
    new_connection_callback_ = callback;
}

void Acceptor::AcceptConnection() {
    struct sockaddr_in client_addr {};
    int new_client_fd = server_sock_->Accept(&client_addr);

    if (new_client_fd != -1) {
        std::cout << "[Acceptor] 成功建立新连接, FD: " << new_client_fd << std::endl;
        if (new_connection_callback_) {
            new_connection_callback_(new_client_fd);
        } else {
            std::cout << "[Acceptor] 警告：上层未注册 NewConnectionCallback" << std::endl;
        }
    }
}