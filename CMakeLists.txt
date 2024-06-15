cmake_minimum_required(VERSION 3.10)
project(Echo_Live_Typetool)

# 默认构建Release版本
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/Echo_Live_Typetool")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug/Echo_Live_Typetool")

# 添加可执行文件
add_executable(Echo_Live_Typetool
    src/main.cpp
    src/funcs.cpp
)

# 包含头文件目录
target_include_directories(Echo_Live_Typetool PRIVATE src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Echo_Live_Typetool PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Echo_Live_Typetool PRIVATE -O3)
endif()