#pragma once 

#include <functional>
#include <memory>

// 纯净的前向声明，不需要 #include "channel.h" 等，极大提升大型项目的编译速度
class EventLoop;
class Socket;
class Channel;

class Acceptor {
public:
    using NewConnectionCallback = std::function<void(int)>;

    Acceptor(EventLoop* loop, int port); // 需要传入 loop 和 port
    ~Acceptor();

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

    void SetNewConnectionCallback(const NewConnectionCallback& callback);

private:
    void AcceptConnection();

    EventLoop* loop_;
    std::unique_ptr<Socket> server_sock_;
    std::unique_ptr<Channel> accept_channel_;

    NewConnectionCallback new_connection_callback_;
};