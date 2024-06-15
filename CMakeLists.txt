cmake_minimum_required(VERSION 3.10)
project(Echo_Live_Typetool)

# 默认构建Release版本
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# C++17
set(CMAKE_CXX_STANDARD 17)

# 输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/release/Echo_Live_Typetool")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug/Echo_Live_Typetool")


add_executable(Echo_Live_Typetool
    src/main.cpp
    src/funcs.cpp
)

# 包含头文件目录

if(WIN32)
    # 设置 pdcurses 库路径  
    set(PDCURSES_DIR ${CMAKE_SOURCE_DIR}/libs/PDCurses)
    include_directories(${PDCURSES_DIR})
    link_directories(${PDCURSES_DIR})
    set(CURSES_LIBRARIES pdcurses)
else()
    find_package(Curses REQUIRED)
    include_directories(${CURSES_INCLUDE_DIR})
endif()

if(WIN32)
    target_link_libraries(Echo_Live_Typetool ${PDCURSES_DIR}/wincon/pdcurses.a)  # Windows 下的动态库或静态库
else()
    target_link_libraries(Echo_Live_Typetool ${PDCURSES_DIR}/x11/libpdcurses.a)  # Linux 或 macOS 下的静态库
endif()

target_include_directories(Echo_Live_Typetool PRIVATE src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Echo_Live_Typetool PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Echo_Live_Typetool PRIVATE -O3)
endif()