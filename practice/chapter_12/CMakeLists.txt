cmake_minimum_required(VERSION 3.10)

project(exercisex)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "choose the type of build" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
endif()

# add_executable(a.out exercises2.cpp exercises2_main.cpp)
# add_executable(a.out exercises3.cpp exercises3_main.cpp)
add_executable(a.out exercises4.cpp exercises4_main.cpp)

target_include_directories(a.out PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})