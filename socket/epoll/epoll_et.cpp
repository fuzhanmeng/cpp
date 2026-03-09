#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cerrno>
#include <csignal>
#include <iostream>
#include <unordered_set>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 4096;
constexpr int kMaxEvents = 128;

volatile std::sig_atomic_t g_running = true;

void SignalHandler(int signum) {
    if (signum == SIGINT) {
        g_running = 0;
    }
}

// 将 FD 设置为非阻塞模式
bool SetNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        std::cout << "set non-blocking fail" << std::endl;
        return false;
    }
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK) != -1;
}

int main() {
    // 1. set signal
    std::signal(SIGPIPE, SIG_IGN);
    std::signal(SIGINT, SignalHandler);

    // 2. create listen fd
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cerr << "create listen fd fail" << std::endl;
        return -1;
    }

    // 3. set addr reuse
    int opt = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "set address reuse fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 4. set addr
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 5. bind
    if (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "bind fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 6. listen
    if (listen(listen_fd, SOMAXCONN) == -1) {
        std::cerr << "listen fail" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 7. listen fd set non-blocking
    SetNonBlocking(listen_fd);

    // 8. create epoll fd
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        std::cerr << "create epoll fd fail" << std::endl;
        return -1;
    }

    // 9. set epoll events
    struct epoll_event event {};
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = listen_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event);

    // 10. ready
    std::unordered_set<int> client_fds;
    std::array<struct epoll_event, kMaxEvents> event_array{};

    std::cout << "EPOLL SERVER START!!!" << std::endl;

    while (g_running) {
        // 1. get ready fd
        int ready_num = epoll_wait(epoll_fd, event_array.data(), event_array.size(), -1);
        if (ready_num < 0) {
            if (errno == EINTR) {
                std::cout << "" << std::endl;
                continue;
            }
            std::cout << "ERROR, SOMETHING BREAK" << std::endl;
            // return -1;
            break;
        }

        // 2. start work
        for (int i = 0; i < ready_num; ++i) {
            int active_fd = event_array[i].data.fd;

            // 1. if a new connect
            if (active_fd == listen_fd) {
                while (true) {
                    struct sockaddr_in client_addr {};
                    socklen_t client_len = sizeof(client_addr);

                    int new_client = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);

                    if (new_client == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            std::cout << "" << std::endl;
                            break;
                        }
                        std::cerr << "accept error" << std::endl;
                        break;
                    }

                    std::cout << "a new client: " << new_client << ", connect success" << std::endl;
                    SetNonBlocking(new_client);
                    client_fds.emplace(new_client);

                    // add new client fd to epoll_fd
                    struct epoll_event client_event {};
                    client_event.events = EPOLLIN | EPOLLET;
                    client_event.data.fd = new_client;
                    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_client, &client_event);
                }
            } else {
                // 2. old client send message to server
                while (true) {
                    std::array<char, kBufferSize> buffer{};
                    ssize_t bytes_recv = recv(active_fd, buffer.data(), buffer.size() - 1, 0);

                    if (bytes_recv > 0) {
                        std::cout << "epoll server recv a message: " << buffer.data() << std::endl;

                        // send
                        ssize_t bytes_send = send(active_fd, buffer.data(), bytes_recv, 0);
                        if (bytes_send > 0) {
                            std::cout << "send message success: " << buffer.data();
                        }
                    } else if (bytes_recv == 0) {
                        std::cout << "client: " << active_fd << ", break" << std::endl;
                        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, active_fd, nullptr);
                        client_fds.erase(active_fd);
                        close(active_fd);
                        break;
                    } else {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            std::cout << "" << std::endl;
                            break;
                        } else {
                            std::cerr << "error, client " << active_fd << ", has something error" << std::endl;
                            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, active_fd, nullptr);
                            client_fds.erase(active_fd);
                            close(active_fd);
                            break;
                        }
                    }
                }
            }
        }
    }

    // end
    std::cout << "epoll exiting..." << std::endl;
    for (int fd : client_fds) {
        // close fd
        shutdown(fd, SHUT_WR);
        close(fd);
    }

    close(epoll_fd);
    close(listen_fd);
    return 0;
}