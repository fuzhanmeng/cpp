#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <iostream>
#include <string>

constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;

int main() {
    // 1. 创建 client fd
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd == -1) {
        std::cout << "创建客户端 socket 失败" << std::endl;
        return -1;
    }

    // 2. 填充服务器信息
    struct sockaddr_in server_addr {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(kServerPort);

    // 修复：inet_pton 成功时返回 1
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) != 1) {
        std::cout << "IP 地址转换失败或无效" << std::endl;
        close(client_fd);
        return -1;
    }

    // 3. 连接服务器
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cout << "连接服务器失败" << std::endl;
        close(client_fd);
        return -1;
    }

    std::cout << "成功连接到服务器！可以开始聊天了 (输入 quit 或 exit 退出)" << std::endl;

    // 4. 开始进行消息传递
    std::string input_msg;
    std::array<char, kBufferSize> buffer{};

    // 将网络字节序IP转换为字符
    std::array<char, INET_ADDRSTRLEN> ip_str{};
    if (inet_ntop(AF_INET, &server_addr.sin_addr.s_addr, ip_str.data(), ip_str.size()) == nullptr) {
        std::cout << "无法将服务器 IP 转回字符串" << std::endl;
    }

    while (true) {
        std::getline(std::cin, input_msg);

        if (input_msg.empty()) {
            continue;
        }

        if (input_msg == "quit" || input_msg == "exit") {
            std::cout << "主动断开连接。" << std::endl;
            break;
        }

        // 5. 发送消息
        if (send(client_fd, input_msg.c_str(), input_msg.size(), 0) == -1) {
            std::cout << "发送消息失败" << std::endl;
            break;
        }

        // 6. 接收消息
        buffer.fill('\0');
        ssize_t bytes_read = recv(client_fd, buffer.data(), buffer.size() - 1, 0);

        if (bytes_read > 0) {
            std::cout << "recv mrssage form : " << ip_str.data() << ", port: " << ntohs(server_addr.sin_port)
                      << std::endl;
            std::cout << "recv message success: " << buffer.data() << std::endl;
        } else if (bytes_read == 0) {
            std::cout << "服务器主动断开了连接" << std::endl;
            break;
        } else {
            std::cout << "接收数据发生网络错误" << std::endl;
            break;
        }
    }

    close(client_fd);
    return 0;
}