#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <iostream>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;

int main() {
    // 1. 创建 UDP socket
    int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd == -1) {
        std::cout << "创建socket失败" << std::endl;
        return -1;
    }

    // 2. 填充服务器地址
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // 3. 绑定信箱
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cout << "绑定失败" << std::endl;
        close(server_fd);
        return -1;
    }

    std::cout << "UDP 服务器启动成功... " << std::endl;

    std::array<char, kBufferSize> buffer{};

    // 4. 开启极简循环：收信 -> 回信
    while (true) {
        struct sockaddr_in client_addr {};
        socklen_t client_len = sizeof(client_addr);
        buffer.fill('\0');

        ssize_t bytes_recv =
            recvfrom(server_fd, buffer.data(), buffer.size() - 1, 0, (struct sockaddr*)&client_addr, &client_len);

        if (bytes_recv > 0) {
            std::cout << "收到客户端消息: " << buffer.data() << std::endl;

            // 💡 第一个参数必须是 server_fd！
            ssize_t bytes_send =
                sendto(server_fd, buffer.data(), bytes_recv, 0, (struct sockaddr*)&client_addr, client_len);
            if (bytes_send > 0) {
                std::cout << "回信成功！" << std::endl;
            } else {
                std::cout << "回信失败！" << std::endl;
            }
        } else if (bytes_recv < 0) {
            std::cout << "网络接收发生异常" << std::endl;
            break;
        }
    }

    close(server_fd);
    return 0;
}