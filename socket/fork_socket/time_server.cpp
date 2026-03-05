#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <cerrno>
#include <chrono>
#include <csignal>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>

constexpr int kServerPort = 8888;

std::atomic<bool> g_is_running{true};

// 信号处理
void SignalHandler(int signum) {
    if (signum == SIGINT || signum == SIGTERM) {
        g_is_running = false;
    }
}

void RegisterSignals() {
    struct sigaction sa {};
    sa.sa_handler = SignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);

    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
}

std::string GetCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm local_tm{};
    localtime_r(&now_time_t, &local_tm); // Linux 线程安全获取时间

    std::ostringstream oss;
    // 格式化输出，末尾加个换行符 \n，让客户端打印出来更好看
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S\n");
    return oss.str();
}
int main() {
    // 处理信号
    RegisterSignals();

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cout << "创建监听fd失败" << std::endl;
        return -1;
    }

    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cout << "绑定失败" << std::endl;
        close(listen_fd);
        return -1;
    }

    if (listen(listen_fd, SOMAXCONN) == -1) {
        std::cout << "监听失败" << std::endl;
        close(listen_fd);
        return -1;
    }

    while (g_is_running) {
        struct sockaddr_in client_addr {};
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd == -1) {
            std::cout << "接收连接失败" << std::endl;
            if (errno == EINTR) {
                continue;
            }
        }

        std::string time_str = GetCurrentTime();
        send(client_fd, time_str.c_str(), time_str.size(), 0);
        std::cout << "已向客户端发送时间，正在断开连接..." << std::endl;
        close(client_fd);
    }

    close(listen_fd);
}