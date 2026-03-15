#pragma once

#include <algorithm>
#include <cstddef> // 提供 size_t
#include <string>
#include <vector>

constexpr int kBufferSize = 1024;

class Buffer {
public:
    // 构造函数：初始化时为底层 vector 分配默认大小
    explicit Buffer(size_t initial_size = kBufferSize) : buffer_(initial_size), readerIndex_(0), writerIndex_(0) {}

    ~Buffer() = default;

    // 1. 核心状态查询
    // 返回可读的有效业务数据字节数
    size_t ReadableBytes() const { return writerIndex_ - readerIndex_; }

    // 返回尾部可直接写入的空闲字节数
    size_t WritableBytes() const { return buffer_.size() - writerIndex_; }

    // 返回头部已经被读取过、可被回收覆盖的废弃字节数
    size_t PrependableBytes() const { return readerIndex_; }

    // 2. 顶层读取动作
    // 偷看数据：返回指向可读数据首地址的常量指针
    const char* Peek() const { return Begin() + readerIndex_; }

    // 提取数据：推进读索引
    void Retrieve(size_t len) {
        if (len < ReadableBytes()) {
            readerIndex_ += len;
        } else {
            RetrieveAll();
        }
    }

    // 提取全部数据：读写索引强行复位，防止内存碎片向后滑动
    void RetrieveAll() {
        readerIndex_ = 0;
        writerIndex_ = 0;
    }

    // 业务层便捷接口：将当前所有可读数据转化为 std::string，并清空缓冲区
    std::string RetrieveAllAsString() {
        std::string str(Peek(), ReadableBytes());
        RetrieveAll();
        return str;
    }

    // 3. 底层写入动作 (供底层网络 I/O 使用)

    // 核心追加函数：实现在 buffer.cpp 中
    void Append(const char* data, size_t len);

    // 重载版本：方便直接追加 std::string
    void Append(const std::string& str) { Append(str.data(), str.size()); }

private:
  
    // 辅助函数：获取底层动态数组的绝对物理首地址
    char* Begin() { return buffer_.data(); }
    const char* Begin() const { return buffer_.data(); }

    // 核心内存伸缩函数：实现在 buffer.cpp 中
    void MakeSpace(size_t len);

    // 物理数据成员
    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
};