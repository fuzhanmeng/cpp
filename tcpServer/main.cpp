#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <array>
#include <cstdlib>
#include <iostream>

#include "socket.h"
constexpr int kServerPort = 8888;
constexpr int kBufferSize = 1024;

int main() {
    Socket server_sock;

    server_sock.BindAddress(kServerPort);
    server_sock.Listen();
    // server_sock.SetNonBlocking();
    std::cout << "the server start,listen 8888 prot" << std::endl;

    struct sockaddr_in client_addr {};

    int client_fd = server_sock.Accept(&client_addr);
    if (client_fd != -1) {
        Socket client_sock(client_fd);

        std::array<char, kBufferSize> buffer{};
        ssize_t bytes_read = ::read(client_sock.fd(), buffer.data(), buffer.size() - 1);
        if (bytes_read > 0) {
            std::cout << "收到消息: " << buffer.data() << std::endl;
            // 💡 收到什么，就原样弹回多少个字节
            ::write(client_sock.fd(), buffer.data(), bytes_read);
        }
    }

    return 0;
}