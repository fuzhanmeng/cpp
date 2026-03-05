#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <iostream>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;

int main() {
    // 1. 创建客户端 socket fd
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cout << "创建socket fd失败" << std::endl;
        return -1;
    }

    // 2. 填充server_addr
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr) != 1) {
        std::cout << "地址无效或者地址转换失败" << std::endl;
        close(client_fd);
        return -1;
    }

    std::array<char, kBufferSize> buffer{};

    // 3. 开始连接服务器
    while (true) {
        if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            std::cout << "客户端连接失败" << std::endl;
            close(client_fd);
            return -1;
        }

        while (true) {
            ssize_t bytes_read = recv(client_fd, buffer.data(), buffer.size() - 1, 0);
            if (bytes_read > 0) {
                std::cout << "time is: " << buffer.data() << std::endl;
            } else if (bytes_read == 0) {
                std::cout << "服务器主动断开连接" << std::endl;
                break;
            } else {
                std::cout << "意外断开" << std::endl;
                break;
            }
        }
    }

    close(client_fd);
    return 0;
}
