#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "buffer.h"

// 前向声明：保持头文件极度纯净
class EventLoop;
class Acceptor;
class TcpConnection;
class EventLoopThreadPool;

class TcpServer {
public:
    // 向上层业务暴露的回调类型：用户只关心“哪个连接发来了消息”
    using MessageCallback = std::function<void(TcpConnection*, Buffer*)>;

    // 构造函数：并指定监听端口
    TcpServer(EventLoop* loop, int port);
    ~TcpServer();

    // 严禁拷贝：Server 是全局唯一的实体，独占底层监听资源
    TcpServer(const TcpServer&) = delete;
    TcpServer& operator=(const TcpServer&) = delete;

    // 设置底层 Sub Reactor 的线程数量,必须在 Start() 之前调用
    void SetThreadNum(int num_threads);

    // 启动服务器
    void Start();

    // main函数注入业务处理逻辑
    void SetMessageCallback(const MessageCallback& callback);

private:
    // 内部槽函数 1：当有新连接到来时触发。
    void HandleNewConnection(int new_client_fd);

    // 内部槽函数 2：当客户端断开时触发。
    void HandleCloseConnection(TcpConnection* conn);

    EventLoop* loop_; // Main Reactor：专职负责 Acceptor
    std::unique_ptr<Acceptor> acceptor_;

    // 独占底层的事件循环线程池
    std::unique_ptr<EventLoopThreadPool> thread_pool_;

    std::unordered_map<int, std::unique_ptr<TcpConnection>> connections_;
    MessageCallback message_callback_;
};