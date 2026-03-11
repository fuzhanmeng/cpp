#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>

#include <cstdint>

class Socket {
public:
    Socket();

    explicit Socket(int fd);

    // 负责 close(fd_)
    ~Socket();

    // 禁用拷贝构造和拷贝赋值（防止多个对象 close 同一个 fd）
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    void BindAddress(uint16_t port);

    void Listen();

    int Accept(struct sockaddr_in* client_addr);

    void SetNonBlocking();

    int fd() const;

private:
    int fd_;
};