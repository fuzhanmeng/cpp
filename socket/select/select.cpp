#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>
#include <vector>

constexpr int kServerPort = 9999;
constexpr int kBufferSize = 4096;

// 必须使用 volatile sig_atomic_t！这是 C/C++ 标准中唯一保证在信号中断时绝对读写安全的类型
volatile std::sig_atomic_t g_running = 1;

void SignalHandler(int signum) {
    if (signum == SIGINT) {
        g_running = 0;
    }
}

int main() {
    // signale handler
    // 1. 忽略 SIGPIPE（写入已断开的 Socket 时不崩溃，而是让 send 返回 -1）
    std::signal(SIGPIPE, SIG_IGN);
    // 2. 截获 Ctrl+C (SIGINT)，交给我们的函数处理
    std::signal(SIGINT, SignalHandler);

    // 1. create listen_fd
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cerr << "create listen_fd fail" << std::endl;
        return -1;
    }

    // 2. server addr
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. bind
    if (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "bind fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 4. listen
    if (listen(listen_fd, SOMAXCONN) == -1) {
        std::cerr << "listen fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    std::cout << "select server start success, listen the port: " << kServerPort << std::endl;

    // 5. select
    std::vector<int> client_fds;
    while (g_running) {
        fd_set read_fds;

        // 1. 清空read_fds
        FD_ZERO(&read_fds);

        // 2. add listen to read_fds
        FD_SET(listen_fd, &read_fds);
        int max_fd = listen_fd;

        // 3. 遍历并把所有fd的名字也写进记事本
        for (int fd : client_fds) {
            FD_SET(fd, &read_fds);
            if (fd > max_fd) {
                max_fd = fd;
            }
        }

        int activity = select(max_fd + 1, &read_fds, nullptr, nullptr, nullptr);
        if (activity < 0) {
            if (errno == EINTR) {
                continue;
            }
            std::cerr << "error, break" << std::endl;
            break;
        }

        // a new connect
        if (FD_ISSET(listen_fd, &read_fds)) {
            struct sockaddr_in client_addr {};
            socklen_t client_len = sizeof(client_addr);

            int new_client = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
            if (new_client > 0) {
                std::cout << "a new connect is coming, new fd: " << new_client << std::endl;
                client_fds.push_back(new_client);
            }
        }

        // old fd
        for (auto it = client_fds.begin(); it != client_fds.end();) {
            int fd = *it;

            if (FD_ISSET(fd, &read_fds)) {
                std::array<char, kBufferSize> buffer{};
                ssize_t bytes_recv = recv(fd, buffer.data(), buffer.size() - 1, 0);

                if (bytes_recv > 0) {
                    std::cout << "fd: " << fd << "recv message: " << buffer.data() << std::endl;

                    ssize_t bytes_send = send(fd, buffer.data(), bytes_recv, 0);
                    if (bytes_send > 0) {
                        std::cout << "fd: " << fd << "send success" << "the message is: " << buffer.data() << std::endl;
                    }
                    it++;
                } else if (bytes_recv == 0) {
                    std::cout << "fd: " << "disconnect" << std::endl;
                    close(fd);
                    it = client_fds.erase(it);
                } else {
                    it++;
                }
            } else {
                it++;
            }
        }
    }

    // exit
    for (int fd : client_fds) {
        const char* bye = "server is exiting, bye";
        send(fd, bye, strlen(bye), 0);
        close(fd);
    }
    close(listen_fd);
    return 0;
}
