#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <system_error>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;
constexpr int kArraySize = 1024;
constexpr int kFilenameSize = 256;

struct FileHeader {
    std::array<char, kFilenameSize> filename_{};
    uint64_t filesize_;
};

bool SendFile(int sendfd, const std::filesystem::path& file_path) {
    // 1. 检查文件是否存在且是一个普通文件（不是目录
    std::error_code ec;
    if (!std::filesystem::is_regular_file(file_path, ec)) {
        std::cerr << "发送失败：文件不存在或不是普通文件 [" << file_path << "]\n";
        return false;
    }

    // 2. 直接获取文件大小，不需要再打开文件再移动光标
    uint64_t filesize = std::filesystem::file_size(file_path, ec);
    if (ec) {
        std::cerr << "获取文件大小失败: " << ec.message() << '\n';
        return false;
    }

    // 3. 从完整路径中自动提取出文件名 (例如从 "/a/b/c.log" 提取 "c.log")
    std::string filename = file_path.filename().string();
    if (filename.length() >= kFilenameSize) {
        std::cerr << "发送失败， 文件名过长" << std::endl;
        return false;
    }

    // 4. 制作文件发送头
    FileHeader header{};
    std::copy(filename.begin(), filename.end(), header.filename_.begin());
    header.filesize_ = filesize;

    // 5. 发送hander
    if (send(sendfd, &header, sizeof(header), 0) == -1) {
        std::cerr << "发送失败" << std::endl;
        return -1;
    }

    // 6. 打开文件准备读取
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "打开文件失败" << std::endl;
        return -1;
    }

    // 7. 分块发送文件
    std::array<char, kBufferSize> buffer{};
    while (true) {
        file.read(buffer.data(), buffer.size());
        std::streamsize bytes_read = file.gcount();
        if (bytes_read > 0) {
            ssize_t bytes_send = send(sendfd, buffer.data(), bytes_read, 0);
            if (bytes_send <= 0) {
                std::cerr << "文件传输中断" << std::endl;
                return false;
            }
        } else {
            break;
        }
    }

    std::cout << "文件 [" << filename << "], 大小: " << filesize << " bytes, 发送完毕\n";
    return true; // 正常结束，返回 true
}

int main() {
    // 1. 客户端创建socket fd
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cerr << "创建socket fd 失败" << std::endl;
        return -1;
    }

    // 2. 填充服务器 信息
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) == -1) {
        std::cerr << "IP 地址转换失败" << std::endl;
        close(client_fd);
        return -1;
    }

    // 3. 连接服务器
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "连接服务器失败" << std::endl;
        close(client_fd);
        return -1;
    }

    // 4. 开始进行消息传输
    std::string input_msg;
    std::array<char, kArraySize> buffer{};

    std::cout << "成功连接！请输入消息 (输入 quit 或 exit 退出)" << std::endl;
    while (true) {
        std::getline(std::cin, input_msg);

        // 如果输入了空格 继续运行
        if (input_msg.empty()) {
            continue;
        }

        // 如果要退出
        if (input_msg == "quit" || input_msg == "exit") {
            break;
        }

        // 发送信息
        SendFile(client_fd, "/home/xm/github/cpp/socket/sendfile/all.log");
        std::cout << "已发送: " << input_msg << std::endl;

        // 接收信息
        buffer.fill('\0');
        ssize_t bytes_recevied = recv(client_fd, buffer.data(), buffer.size() - 1, 0);

        if (bytes_recevied > 0) {
            std::cout << "接收消息成功， 服务器回应: " << buffer.data() << std::endl;
        } else if (bytes_recevied == 0) {
            std::cout << "服务器已经断开了连接" << std::endl;
        } else {
            std::cerr << "接收数据出错" << std::endl;
        }
    }

    // 5. 结束 关闭socket
    close(client_fd);
    return 0;
}