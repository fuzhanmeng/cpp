#include "socket.h"

#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <iostream>

Socket::Socket() {
    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ == -1) {
        std::cout << "create listen fd fail" << std::endl;
        abort();
    }
}

Socket::Socket(int fd) : fd_(fd) {}

Socket::~Socket() {
    if (fd_ != -1) {
        ::close(fd_);
        std::cout << "Socket [FD: " << fd_ << "] 已自动销毁并回收资源" << std::endl;
    }
}

void Socket::BindAddress(uint16_t port) {
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << "address reuse fail" << std::endl;
    }

    if (::bind(fd_, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "bind fail" << std::endl;
        abort();
    }
}

void Socket::Listen() {
    if (listen(fd_, SOMAXCONN) == -1) {
        std::cerr << "listen fail" << std::endl;
        abort();
    }
}

int Socket::Accept(struct sockaddr_in* client_addr) {
    socklen_t client_len = sizeof(struct sockaddr_in);
    int client_fd = accept4(fd_, (struct sockaddr*)client_addr, &client_len, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (client_fd == -1) {
        // 在非阻塞 Listening Socket 下，EAGAIN 和 EWOULDBLOCK 是正常现象（没有新连接了）
        if (errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
            std::cerr << "[Socket] accept4 发生底层错误,errno: " << errno << std::endl;
        }
        return -1;
    }
    return client_fd;
}

void Socket::SetNonBlocking() {
    int flags = ::fcntl(fd_, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "获取 fcntl 标志失败" << std::endl;
        abort();
    }

    if (::fcntl(fd_, F_SETFL, flags | O_NONBLOCK) == -1) {
        std::cerr << "set O_NONBLOCK fail" << std::endl;
        abort();
    }
}

int Socket::fd() const { return fd_; }