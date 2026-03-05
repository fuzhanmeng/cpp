#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;

int main() {
    // 1. 创建socket fd
    int client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd == -1) {
        std::cout << "创建client fd 失败" << std::endl;
        return -1;
    }

    // 2. 要发给哪个服务器
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr) != 1) {
        std::cout << "地址转换失败" << std::endl;
    }

    // 3. 直接开始收发消息
    std::string input_msg;
    std::array<char, kBufferSize> buffer{};

    std::array<char, INET_ADDRSTRLEN> server_ip;
    if (inet_ntop(AF_INET, &server_addr.sin_addr.s_addr, server_ip.data(), server_ip.size()) != nullptr) {
        std::cout << "网络IP转字符IP成功" << std::endl;
    }

    while (true) {
        std::cout << "send message: " << std::endl;
        std::getline(std::cin, input_msg);
        if (input_msg.empty()) {
            std::cout << "输入了空格，继续" << std::endl;
            continue;
        }

        if (input_msg == "quit") {
            std::cout << "输入了 quit,退出" << std::endl;
            close(client_fd);
            break;
            ;
        }

        ssize_t bytes_send = sendto(client_fd, input_msg.c_str(), input_msg.size(), 0, (struct sockaddr*)&server_addr,
                                    sizeof(server_addr));
        if (bytes_send > 0) {
            std::cout << "send messge success" << std::endl;
        } else if (bytes_send == -1) {
            std::cout << "send message fail" << std::endl;
        }

        // 开始接收
        buffer.fill('\0');
        ssize_t bytes_recv = recvfrom(client_fd, buffer.data(), buffer.size() - 1, 0, nullptr, nullptr);
        if (bytes_recv > 0) {
            std::cout << "recv message from " << server_ip.data() << ", message: " << buffer.data() << std::endl;
        } else if (bytes_recv == 0) {
            std::cout << "服务器断开了连接" << std::endl;
        } else {
            std::cout << "崩溃中断" << std::endl;
        }
    }

    close(client_fd);
    return 0;
}