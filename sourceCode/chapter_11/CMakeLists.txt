# 指定CMake所需的最低版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(Time)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake在构建目录生成一个 compile_commands.json文件
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 创建可执行文件
# add_executable(a.out 11.2_mytime0.cpp 11.3_usetime0.cpp)
add_executable(a.out 11.5_mytime1.cpp 11.6_usetime1.cpp)

# 设置目标的包含目录（头文件路径）
target_include_directories(a.out PRIVATE ${CMAKE_CURRENT_S})