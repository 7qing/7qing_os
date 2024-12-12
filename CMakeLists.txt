cmake_minimum_required(VERSION 3.8)

project(7qing_os VERSION 1.0
                  DESCRIPTION "my_first_system_kernel"
                  LANGUAGES C CXX ASM ASM_NASM)

# 设置全局变量
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)
set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)

# 创建输出目录
file(MAKE_DIRECTORY ${BIN_DIR})
file(MAKE_DIRECTORY ${BUILD_DIR})

# 设置 NASM 编译器路径
find_program(NASM_EXECUTABLE nasm REQUIRED)

# 添加 src 子目录
add_subdirectory(src)

# 添加清理目标
add_custom_target(
    clean
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${BIN_DIR}/* ${BUILD_DIR}/*
    COMMENT "Cleaning up build files"
)

