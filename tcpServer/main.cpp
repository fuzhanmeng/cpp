#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <csignal>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "channel.h"
#include "epoll.h"
#include "event_loop.h"
#include "socket.h"

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;

int main() {
    // 1. 信号处理：忽略 SIGPIPE，防止对端 RST 导致进程崩溃
    ::signal(SIGPIPE, SIG_IGN);

    // 2. 初始化核心分发器 (Event Dispatcher)
    EventLoop loop;

    // 3. 初始化 Listening Socket (Acceptor)
    Socket server_sock;
    server_sock.BindAddress(kServerPort);
    server_sock.Listen();
    server_sock.SetNonBlocking();

    std::cout << "Reactor Server started. Listening on port: " << kServerPort << std::endl;

    // 4. 连接上下文管理：维护 Client Sockets 及其绑定的 Channels
    std::unordered_map<int, std::unique_ptr<Socket>> client_sockets;
    std::unordered_map<int, std::unique_ptr<Channel>> client_channels;

    // 5. 为 Acceptor 封装 Channel
    Channel server_channel(&loop, server_sock.fd());

    server_channel.SetReadCallback([&]() {
        struct sockaddr_in client_addr {};
        int new_client_fd = server_sock.Accept(&client_addr);
        std::cout << "[底层诊断] Acceptor 预案执行！准备调用 Accept..." << std::endl;
        if (new_client_fd != -1) {
            // A. 封装 Connected Socket 并设置为非阻塞模式
            auto client_sock = std::make_unique<Socket>(new_client_fd);
            client_sock->SetNonBlocking();
            // B. 为 Connected Socket 封装 Channel
            auto client_channel = std::make_unique<Channel>(&loop, new_client_fd);
            // C. 注册 Connected Socket 的 ReadCallback (处理 I/O 读写)
            client_channel->SetReadCallback([new_client_fd, &client_sockets, &client_channels]() {
                std::array<char, kBufferSize> buffer{};
                ssize_t bytes_recv = ::recv(new_client_fd, buffer.data(), buffer.size() - 1, 0);

                if (bytes_recv > 0) {
                    std::cout << "recv message from: " << new_client_fd << ", the message is: " << buffer.data()
                              << std::endl;

                    ssize_t bytes_send = ::send(new_client_fd, buffer.data(), bytes_recv, MSG_NOSIGNAL);

                    if (bytes_send > 0) {
                        std::cout << "send message success" << std::endl;
                    }

                } else if (bytes_recv == 0) {
                    std::cout << "the client disconnect" << std::endl;
                    client_sockets.erase(new_client_fd);
                    client_channels.erase(new_client_fd);
                    std::cout << "total active connection is: " << client_sockets.size() << std::endl;
                } else if (bytes_recv < 0) {
                    if (errno != EAGAIN && errno != EWOULDBLOCK) {
                        std::cout << "ERROR" << std::endl;
                        client_sockets.erase(new_client_fd);
                        client_channels.erase(new_client_fd);
                    }
                }
            });

            // D. 向 Epoll 注册 EPOLLIN 事件
            client_channel->EnableRead();

            // E. 转移所有权至 map 进行生命周期持久化
            client_sockets[new_client_fd] = std::move(client_sock);
            client_channels[new_client_fd] = std::move(client_channel);

            std::cout << "a new connection fd: " << new_client_fd
                      << ", total active connections is: " << client_sockets.size() << std::endl;
        }
    });

    std::cout << "1111" << std::endl;
    // 7. 向 Epoll 注册 Acceptor 的 EPOLLIN 事件
    server_channel.EnableRead();

    std::cout << "2222" << std::endl;

    // 8. 启动 EventLoop，进入阻塞轮询状态
    loop.Loop();

    return 0;
}