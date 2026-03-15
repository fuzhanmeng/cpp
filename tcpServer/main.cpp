#include <iostream>
#include <string>

#include "event_loop.h"
#include "tcp_server.h"
#include "tcp_connection.h"
#include "buffer.h"
#include "length_header_codec.h" // TLV 编解码器

constexpr int kServerPort = 8888;
LengthHeaderCodec* g_codec = nullptr;

// 运行在底层的 Sub Reactor 子线程中！
// 注意：由于配置了 4 个工作线程，这个函数会被 4 个不同的线程并发调用。
// 但对于同一个 TcpConnection 而言，它永远是串行触发的，天生线程安全。
void OnBusinessMessage(TcpConnection* conn, uint32_t type, const std::string& payload) {
    std::cout << "[业务层] 收到完整业务帧！"
              << " | FD: " << conn->fd() 
              << " | Type: " << type 
              << " | 载荷长度: " << payload.size() << " 字节" << std::endl;

    // 业务处理与响应
    std::string response = "Server Echo (Multi-Threaded): " + payload;

    // 异步发送响应，Codec 会自动进行大端序转换和 TLV 封包
    if (g_codec) {
        g_codec->Send(conn, type, response);
    }
}

int main() {
    std::cout << "=== 高性能 Reactor 网络服务器启动 (主从多线程架构) ===" << std::endl;

    // 1. 初始化 Main Reactor (专职负责 Acceptor 接收新连接)
    EventLoop main_loop;

    // 2. 初始化 TcpServer
    TcpServer server(&main_loop, kServerPort);

    // 3. 开启 4 个 Sub Reactor 工作线程！
    server.SetThreadNum(4);

    // 4. 初始化 Codec 并组装业务流向
    LengthHeaderCodec codec(OnBusinessMessage);
    g_codec = &codec;

    // 5. 架构拦截：注册底层字节流回调给 Codec
    server.SetMessageCallback([&codec](TcpConnection* conn, Buffer* buffer) {
        codec.OnRawMessage(conn, buffer);
    });

    // 6. 物理启动：触发线程池创建，开启服务
    server.Start();

    std::cout << "服务器正在监听端口: " << kServerPort << "，等待客户端连接..." << std::endl;

    // 7. 挂起主线程，进入 Main Reactor 的无限事件轮询
    main_loop.Loop();

    return 0;
}