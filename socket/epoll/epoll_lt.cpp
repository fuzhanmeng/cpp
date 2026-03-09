#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_set>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 4096;
constexpr int kMaxEvents = 64;

volatile std::sig_atomic_t g_running = 1;

void SignalHandler(int signum) {
    if (signum == SIGINT) {
        g_running = false;
    }
}

bool SetNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        return false;
    }

    return fcntl(fd, F_SETFL, flags | O_NONBLOCK) != -1;
}

int main() {
    // 1. set signal
    std::signal(SIGPIPE, SIG_IGN);
    std::signal(SIGINT, SignalHandler);

    // 2. listen fd
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cout << "create listen fd fail" << std::endl;
    }

    // 3. set reuseaddr
    int opt = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "reuseaddr fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 4. set server addr
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 5. bind
    if (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cout << "bind fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 6. listen
    if (listen(listen_fd, SOMAXCONN) == -1) {
        std::cerr << "listen faile" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 7. set non-blocking
    if (SetNonBlocking(listen_fd) == false) {
        std::cerr << "set non-blocking fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    std::cout << "epoll server start success, listen the port: " << kServerPort << std::endl;

    // 8. start epoll
    // 只要我的程序去启动别的外部程序，立刻帮我把这把 epoll_fd 钥匙销毁，绝对不准传给外人
    int epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    if (epoll_fd == -1) {
        std::cerr << "create epoll fd fail" << std::endl;
        return -1;
    }

    // 9. create epoll event
    struct epoll_event event {};
    event.events = EPOLLIN; // 关心可读事件
    event.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event);

    // 10. client_fds;
    std::unordered_set<int> client_fds{};

    // 用来接 epoll_wait 扔出来的活跃事件 一次最多处理kMaxEvents个事件
    std::array<struct epoll_event, kMaxEvents> events_array{};

    // 11. Event Loop
    while (g_running) {
        int num_ready = epoll_wait(epoll_fd, events_array.data(), events_array.size(), -1);

        if (num_ready < 0) {
            if (errno == EINTR) {
                std::cout << "Ctrl + C" << std::endl;
                continue;
            }
        }

        for (int i = 0; i < num_ready; ++i) {
            int active_fd = events_array[i].data.fd;

            // 1. new client
            if (active_fd == listen_fd) {
                struct sockaddr client_addr {};
                socklen_t client_len = sizeof(client_addr);
                int new_client = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
                if (new_client == -1) {
                    std::cerr << "accept new client fail" << std::endl;
                    close(new_client);
                    return -1;
                } else if (new_client > 0) {
                    std::cout << "new client is accept success" << std::endl;

                    // 1. set non-blocking
                    SetNonBlocking(new_client);

                    // 2. add client_fds
                    client_fds.emplace(new_client);

                    // 3. add epoll_event
                    struct epoll_event client_event {};
                    client_event.events = EPOLLIN;
                    client_event.data.fd = new_client;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_client, &client_event);
                }
            } else {
                // old client

                std::array<char, kBufferSize> buffer{};
                ssize_t bytes_recv = recv(active_fd, buffer.data(), buffer.size() - 1, 0);
                if (bytes_recv > 0) {
                    std::cout << "fd: " << active_fd << ", recv a message: " << buffer.data() << std::endl;

                    ssize_t bytes_send = send(active_fd, buffer.data(), bytes_recv, 0);
                    if (bytes_send > 0) {
                        std::cout << "fd: " << active_fd << ", send a message: " << buffer.data() << std::endl;
                    } else {
                        std::cout << "send fail" << std::endl;
                    }
                } else if (bytes_recv == 0) {
                    std::cout << "client fd: " << active_fd << ", disconnect" << std::endl;

                    // 1. 把他从 epoll 红黑树上除名
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, active_fd, nullptr);
                    // 2. 从哈希表里删掉 (O(1) 速度)
                    client_fds.erase(active_fd);

                    close(active_fd);
                } else {
                    if (errno != EAGAIN && errno != EWOULDBLOCK) {
                        std::cerr << "client  " << active_fd << "发生异常读取错误" << std::endl;

                        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, active_fd, nullptr);
                        client_fds.erase(active_fd);
                        close(active_fd);
                    }
                    break;
                }
            }
        }
    }

    // 逐个关闭clinet_fds
    for (int fd : client_fds) {
        const char* bye = "eploo is exiting, bye";
        send(fd, bye, strlen(bye), 0);
        close(fd);
    }

    close(epoll_fd);
    close(listen_fd);
    return 0;
}