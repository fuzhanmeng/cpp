#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <atomic>
#include <csignal>
#include <iostream>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;
constexpr int kBacklog = SOMAXCONN;

// 全局运行标志位（使用原子变量，保证多线程或信号并发修改时的绝对安全）
std::atomic<bool> g_is_running{true};

std::string BuildHttpResponse() {
    std::string body =
        "<html><body><h1>Hello, World!</h1>"
        "<p>这是一个简单的HTTP服务器</p></body></html>";

    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "Content-Length: " +
        std::to_string(body.size()) +
        "\r\n"
        "Connection: close\r\n"
        "\r\n" +
        body;

    return response;
}

void SignalHandler(int) {
    g_is_running.store(false);
}

void RegisterSignals() {
    struct sigaction sa{};
    sa.sa_handler = SignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT,&sa,nullptr);
    sigaction(SIGTERM, &sa, nullptr);

    signal(SIGPIPE, SIG_IGN);
}

int main() {
    RegisterSignals();


    // 创建和绑定socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << "创建socket fd 失败" << std::endl;
        return -1;
    }

    // 设置地址重用
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cout << "设置地址重用失败" << std::endl;
        return -1;
    }

    // 设置服务器信息
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 绑定
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cout << "绑定失败" << std::endl;
        return -1;
    }

    // 开启监听
    if (listen(sockfd, kBacklog) == -1) {
        std::cout << "监听失败" << std::endl;
        return -1;
    }

    std::cout << "HTTP 服务器已启动！请打开浏览器访问 http://127.0.0.1:8888" << std::endl;

    while (g_is_running) {
        // 创建一个socketaddr_in 结构体用于存储客户端信息
        struct sockaddr_in client_addr {};
        std::array<char, kBufferSize> buffer{};
        socklen_t client_len = sizeof(client_addr);

        // 开始接受连接
        int client_fd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            if (errno == EINTR)
                continue; // 信号中断引起的，继续循环
            std::cout << "接受连接失败" << std::endl;
            continue; // 单个连接失败，跳过本次处理
        }
        ssize_t bytes_read = recv(client_fd, buffer.data(), buffer.size() - 1, 0);

        if (bytes_read > 0) {
            std::cout << "recv message from: " << client_addr.sin_addr.s_addr << ", prot: " << client_addr.sin_port
                      << ", the message is " << buffer.data() << std::endl;

            // 发送报文给浏览器
            std::string resopose = BuildHttpResponse();
            ssize_t total_sent = 0;
            send(client_fd, resopose.c_str(), resopose.size(), 0);
        } else {
            std::cout << "接收消息失败" << std::endl;
        }
        if (shutdown(client_fd, SHUT_WR)) {
        }
        close(client_fd);
    }
    close(sockfd);
    return 0;
}