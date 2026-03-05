#include <arpa/inet.h>
#include <asm-generic/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h> // close(fd) or fork or sleep

#include <cstdlib>
#include <iostream>

void ShowSocketOprions(int sockfd) {
    int opt_val;
    socklen_t opt_len = sizeof(opt_val);

    // 获取SO_REUSEADDR选项，即地址是否被重用
    if (getsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, &opt_len) == 0) {
        std::cout << "SO_REUSEADDR: " << (opt_val ? "启用" : "禁用") << std::endl;
    }

    // 获取接收缓冲区大小
    if (getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &opt_val, &opt_len) == 0) {
        std::cout << "接收缓冲区大小: " << opt_val << std::endl;
    }

    // 获取发送缓冲区大小
    if (getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, &opt_val, &opt_len) == 0) {
        std::cout << "发送缓冲区大小: " << opt_val << std::endl;
    }

    // 获取SOCKET类型
    if (getsockopt(sockfd, SOL_SOCKET, SO_TYPE, &opt_val, &opt_len) == 0) {
        if (opt_val == SOCK_STREAM) {
            std::cout << "TCP" << std::endl;
        } else if (opt_val == SOCK_DGRAM) {
            std::cout << "UDP" << std::endl;
        }
    }
}

int main() {
    int sockfd;
    // 创建socket fd
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << "创建socket fd 失败" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 1. 查看默认配置
    ShowSocketOprions(sockfd);

    // 2. 开启地址重用
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. 修改缓冲区大小
    int buffer_size = SOMAXCONN;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &buffer_size, sizeof(buffer_size)) == -1) {
        std::cout << "修改接收缓冲区失败" << std::endl;
    }

    // 4. 再次检查修改后的配置
    ShowSocketOprions(sockfd);

    close(sockfd);
    return 0;
}