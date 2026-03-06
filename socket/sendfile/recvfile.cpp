#include <arpa/inet.h>
#include <bits/types/struct_timeval.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

constexpr int kServerPort = 8888;
constexpr int kArraySize = 4096; // 同样建议改大到 4KB，提升写入性能
constexpr int kFilenameSize = 256;

struct FileHeader {
    std::array<char, kFilenameSize> filename_{};
    uint64_t filesize_;
};

bool RecvFile(int recvfd) {
    FileHeader header{};

    // 1. 读取header
    ssize_t header_read = recv(recvfd, &header, sizeof(header), 0);
    if (header_read <= 0) {
        return false;
    }

    // 2. 获取文件名和文件大小
    std::string filename(header.filename_.data(), strnlen(header.filename_.data(), header.filename_.size()));
    std::cout << "\n>>> 准备接收文件: [" << filename << "], 大小: " << header.filesize_ << " bytes\n";

    // 3. 接收文件
    std::string save_path = "download_" + filename;
    std::ofstream outfile(save_path, std::ios::binary);
    if (!outfile.is_open()) {
        std::cerr << "无法创建本地文件" << std::endl;
        return false;
    }

    std::array<char, kArraySize> buffer{};
    uint64_t remaining_bytes = header.filesize_; // 要接收的文件大小
    while (remaining_bytes > 0) {
        uint64_t to_recv = std::min(static_cast<uint64_t>(buffer.size()), remaining_bytes);

        ssize_t bytes_recv = recv(recvfd, buffer.data(), to_recv, 0);
        if (bytes_recv <= 0) {
            std::cerr << "文件传输中断" << std::endl;
            return false;
        }

        outfile.write(buffer.data(), bytes_recv);
        remaining_bytes -= bytes_recv;
    }

    outfile.close();
    std::cout << "文件 [" << filename << "] 接收完毕并保存至本地\n";
    std::string ack_msg = "服务器已成功保存 " + filename;
    send(recvfd, ack_msg.c_str(), ack_msg.size(), 0);

    return true; // 接收成功，继续保持连接
}

int main() {
    // 1. 服务器端创建监听socket fd
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        std::cout << "创建监听fd 失败" << std::endl;
        return -1;
    }

    // 2. 完善服务器信息
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cout << "设置端口重用失败" << std::endl;
    }

    // 3. 开始绑定
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cout << "绑定失败" << std::endl;
        close(listen_fd);
        return -1;
    }

    // 4. 开启监听
    if (listen(listen_fd, SOMAXCONN) == -1) {
        std::cout << "监听失败" << std::endl;
        return -1;
    }

    std::cout << "服务器已启动，正在监听 8888 端口..." << std::endl;

    while (true) {
        // 5. 开始接收来自客户端的连接
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);

        int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_fd == -1) {
            std::cout << "接收连接失败" << std::endl;
            continue;
        }

        std::cout << "客户端已经成功连接到 IP " << inet_ntoa(client_addr.sin_addr) << std::endl;

        // 6. 接收数据/发送数据
        while (true) {
            if (!RecvFile(client_fd)) {
                std::cout << "客户端断开连接，等待下一个客户端...\n";
                break;
            }
        }
        close(client_fd);
    }

    close(listen_fd);
    return 0;
}