# 1. 规定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 声明项目名称和使用的语言 (CXX 代表 C++)
project(TcpServer LANGUAGES CXX)

# 3. 🌟 现代 C++ 铁律：强制使用 C++17 标准！
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 开启严格的警告模式（防呆神器）和 Debug 调试信息
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# 5. 告诉 CMake，把这几个源文件编译成一个叫 "server" 的可执行程序
# 注意：头文件 socket.h 不需要写在这里，CMake 会自动顺着 #include 找到它
add_executable(server main.cpp socket.cpp epoll.cpp channel.cpp event_loop.cpp)