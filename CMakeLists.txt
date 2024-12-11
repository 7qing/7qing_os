cmake_minimum_required(VERSION 3.1)

project(7qing_os VERSION 1.0
                  DESCRIPTION "my_first_system_kernel"
                  LANGUAGES C CXX ASM ASM_NASM)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加 src 子目录
add_subdirectory(src)

# 定义 NASM 汇编文件路径
set(NASM_FILE ${CMAKE_SOURCE_DIR}/src/boot/boot.asm)

# 定义 NASM 输出文件路径
set(BIN_OUTPUT ${CMAKE_BINARY_DIR}/boot.bin)
set(LST_OUTPUT ${CMAKE_BINARY_DIR}/boot.lst)

# 自定义命令生成 NASM 文件
add_custom_command(
    OUTPUT ${BIN_OUTPUT} ${LST_OUTPUT}
    COMMAND nasm -f bin -o ${BIN_OUTPUT} -l ${LST_OUTPUT} ${NASM_FILE}
    COMMENT "Compiling ${NASM_FILE} with NASM"
)

# 添加目标，确保 custom command 被执行
add_custom_target(
    BootAsm ALL
    DEPENDS ${BIN_OUTPUT} ${LST_OUTPUT}
)

