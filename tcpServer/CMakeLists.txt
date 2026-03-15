# 1. 规定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 声明项目名称和使用的语言
project(TcpServer LANGUAGES CXX)

# 3. 强制使用 C++17 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 🌟 核心编译配置：必须加上 -pthread 以支持底层的 POSIX 线程库！
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -pthread")

# 5. 编译目标文件
# 新增了 event_loop_thread.cpp 和 event_loop_thread_pool.cpp
add_executable(server 
    main.cpp 
    socket.cpp 
    epoll.cpp 
    channel.cpp 
    event_loop.cpp 
    event_loop_thread.cpp         
    event_loop_thread_pool.cpp    
    acceptor.cpp 
    tcp_connection.cpp 
    tcp_server.cpp 
    buffer.cpp
    length_header_codec.cpp     
)