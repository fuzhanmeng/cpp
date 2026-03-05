#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <atomic>
#include <cerrno>
#include <csignal>
#include <iostream>
#include <string>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;

std::atomic<bool> g_is_running{true};

// 处理信号
void SignalHandler(int signum) {
    if (signum == SIGINT || signum == SIGTERM) {
        g_is_running = false;
    }
}

void RegisterSignals() {
    struct sigaction sa {};
    sa.sa_handler = SignalHandler;
    sigemptyset(&sa.sa_mask); // 当我在处理关机信号时，不需要屏蔽其他额外信号
    sa.sa_flags = 0; //

    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);

    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
}

int main() {
    // 1. 处理信号
    RegisterSignals();

    // 2. 创建监听socket fd
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cout << "创建监听fd失败" << std::endl;
        return -1;
    }

    // 3. 填充服务器信息
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 地址重用
    int opt = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cout << "地址重用失败" << std::endl;
    }

    // 4. bind
    if (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cout << "绑定失败" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 5. 开启监听
    if (listen(listen_fd, SOMAXCONN) == -1) {
        std::cout << "监听失败" << std::endl;
        close(listen_fd);
        return -1;
    }

    std::cout << "👑 多进程并发服务器已启动！大堂经理正在 8888 端口迎客..." << std::endl;
    std::array<char, INET_ADDRSTRLEN> ip_str{};
    // 6. 开启循环收发消息
    while (g_is_running) {
        // 构建接收结构体
        struct sockaddr_in client_addr {};
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            if (errno == EINTR) {
                continue;
            }
            std::cout << "服务器接收连接失败" << std::endl;
            close(listen_fd);
            break;
        }

        inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, ip_str.data(), ip_str.size());
        std::cout << "新连接IP: " << ip_str.data() << std::endl;

        // 创建子进程去处理连接
        pid_t pid = fork();
        if (pid < 0) {
            std::cout << "创建子进程失败" << std::endl;
            close(client_fd);
            break;
        } else if (pid == 0) {
            close(listen_fd);
            std::array<char, kBufferSize> buffer{};

            // 收消息
            while (true) {
                buffer.fill('\0');
                ssize_t bytes_read = recv(client_fd, buffer.data(), buffer.size() - 1, 0);

                if (bytes_read > 0) {
                    std::cout << "PID: " << getpid() << "收到消息: " << buffer.data() << std::endl;

                    // 直接回复
                    std::string response = std::string(buffer.data());
                    if (send(client_fd, response.c_str(), response.size(), 0) == -1) {
                        std::cout << "发送失败" << std::endl;
                    } else {
                        std::cout << "发送了: " << response.c_str() << std::endl;
                    }
                } else if (bytes_read == 0) {
                    std::cout << "客户端主动断开连接" << std::endl;
                    break;
                } else {
                    std::cout << "异常中断" << std::endl;
                    break;
                }
            }
            close(client_fd);
        } else {
            close(client_fd);
        }
    }

    close(listen_fd);
    return 0;
}