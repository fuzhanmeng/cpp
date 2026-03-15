#pragma once

#include <functional>
#include <string>

#include "buffer.h"
#include "tcp_connection.h"

// 1. 严格定义的 TLV 物理报头
struct MessageHeader {
    uint32_t message_type_; // 4 字节：消息类型
    uint32_t payload_len_;  // 4 字节：有效载荷长度
};
constexpr size_t kHeaderSize = sizeof(MessageHeader);

class LengthHeaderCodec {
public:
    // 是谁发的（conn），什么指令（type），具体内容是什么（payload）
    using FrameCallback = std::function<void(TcpConnection* conn, uint32_t type, const std::string& payload)>;

    explicit LengthHeaderCodec(const FrameCallback& cb);

    // 解码器
    void OnRawMessage(TcpConnection* conn, Buffer* buffer);

    // 在 payload 前面组装一个 8 字节的 MessageHeader，把 type 和长度填好，然后打包成一整块二进制流，一把推给底层的 TcpConnection::Send 去排队发送
    void Send(TcpConnection* conn, uint32_t type, const std::string& payload);

private:
    FrameCallback frame_callback_;
};