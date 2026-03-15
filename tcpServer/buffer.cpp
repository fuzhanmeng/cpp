#include "buffer.h"

#include <algorithm>
#include <cstddef>

void Buffer::Append(const char* data, size_t len) {
    // 1. 容量检查：如果尾部空闲空间不够，触发内部调整机制
    if (WritableBytes() < len) {
        MakeSpace(len);
    }

    // 2. 物理写入：将新来的数据精准拷贝到写游标 (writerIndex_) 所在的位置
    std::copy(data, data + len, buffer_.begin() + static_cast<std::ptrdiff_t>(writerIndex_));

    // 3. 游标推进：写入完成后，写游标向后移动 len 个单位
    writerIndex_ += len;
}

void Buffer::MakeSpace(size_t len) {
    // 如果 废弃空间 + 尾部空闲空间 < 需要写入的长度 (len)
    if (readerIndex_ + WritableBytes() < len) {
        // 物理扩容,空间是真的不够了，直接向操作系统申请重新分配更大的堆内存
        buffer_.resize(writerIndex_ + len);
    } else {
        // 内部腾挪,空间足够，不需要申请新内存，直接把有效数据平移到 vector 头部
        // 提前保存当前有效数据的总长度
        size_t readbale_len = ReadableBytes();

        std::copy(buffer_.begin() + static_cast<std::ptrdiff_t>(readerIndex_),
                  buffer_.begin() + static_cast<std::ptrdiff_t>(writerIndex_), buffer_.begin());
        readerIndex_ = 0;
        writerIndex_ = readbale_len;
    }
}