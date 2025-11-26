# 指定CMake所需的最低版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(Time LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMake在构建目录生成 compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 如果用户没有指定构建类型，就默认Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build" FORCE)
endif()

# 为Debug构建指定编译选项，保证生成GDB调试信息
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()

# 创建可执行文件
# add_executable(a.out 12.2_stringBag.cpp 12.3_vegnews.cpp)
# add_executable(a.out 12.5_string1.cpp 12.6_sayings1.cpp)
# add_executable(a.out 12.5_string1.cpp 12.7_sayings2.cpp)
# add_executable(a.out 12.8_placenew1.cpp)
# add_executable(a.out 12.9_placenew2.cpp)
add_executable(a.out 12.11_queue.cpp 12.12_bank.cpp)


# 设置目标的包含目录（头文件路径）
target_include_directories(a.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
