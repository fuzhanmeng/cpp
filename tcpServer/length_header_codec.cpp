#include "length_header_codec.h"

#include <arpa/inet.h> // 用于网络字节序转换 (ntohl / htonl)

#include <algorithm> // 用于底层内存拷贝 (std::copy)

// 使用初始化列表
LengthHeaderCodec::LengthHeaderCodec(const FrameCallback& cb) : frame_callback_(cb) {}

// 解码引擎实现：解决 TCP 粘包与半包
void LengthHeaderCodec::OnRawMessage(TcpConnection* conn, Buffer* buffer) {
    while (buffer->ReadableBytes() >= kHeaderSize) {
        MessageHeader header;
        // 零拷贝窥探报头
        std::copy(buffer->Peek(), buffer->Peek() + kHeaderSize, reinterpret_cast<char*>(&header));

        // 将网络大端序转换为当前主机的 CPU 字节序
        uint32_t type = ntohl(header.message_type_);
        uint32_t length = ntohl(header.payload_len_);

        size_t total_frame_len = kHeaderSize + length;

        // 处理半包边界条件：如果 Buffer 里的数据不够一个完整的帧，直接退出循环
        if (buffer->ReadableBytes() < total_frame_len) {
            break;
        }

        // 提取完整的业务载荷 (Payload)
        std::string payload(buffer->Peek() + kHeaderSize, length);

        // 物理推进读游标，回收这段已被解析的内存
        buffer->Retrieve(total_frame_len);

        // 触发高层业务的回调路由
        if (frame_callback_) {
            frame_callback_(conn, type, payload);
        }
    }
}

// 编码引擎实现：封装 TLV 头部并转化为字节流
void LengthHeaderCodec::Send(TcpConnection* conn, uint32_t type, const std::string& payload) {
    MessageHeader header;
    // 强制转换为网络大端序
    header.message_type_ = htonl(type);
    header.payload_len_ = htonl(payload.size());

    Buffer output_buf;

    output_buf.Append(reinterpret_cast<const char*>(&header), kHeaderSize);

    output_buf.Append(payload.data(), payload.size());

    // 移交底层的发送链路去处理拥塞与实际的网络 I/O
    conn->Send(output_buf.RetrieveAllAsString());
}