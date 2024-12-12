cmake_minimum_required(VERSION 3.8)

project(7qing_os VERSION 1.0
                  DESCRIPTION "my_first_system_kernel"
                  LANGUAGES C CXX ASM ASM_NASM)

# 设置全局变量
set(BIN_DIR ${CMAKE_BINARY_DIR}/bin)
set(BUILD_DIR ${CMAKE_BINARY_DIR}/build)

# 全局链接文件
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${CMAKE_SOURCE_DIR}/boot/linker.lds")

# 编译,链接基本参数
add_compile_options(-pipe -ffreestanding -nostdlib -fno-pie -fno-stack-protector -mcmodel=large -fno-asynchronous-unwind-tables)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -z max-page-size=0x1000 -Wl,--build-id=none -static")

#库
include_directories(${PROJECT_SOURCE_DIR}/include)

# 创建输出目录
file(MAKE_DIRECTORY ${BIN_DIR})
file(MAKE_DIRECTORY ${BUILD_DIR})


# 设置 NASM 编译器路径
find_program(NASM_EXECUTABLE nasm REQUIRED)

# 添加 src 子目录
add_subdirectory(boot)
add_subdirectory(kernel)

# 定义虚拟目标，确保 src 的构建包含 boot 和 kernel
add_custom_target(
    all_src
    DEPENDS ${BIN_DIR}/boot.bin ${BUILD_DIR}/kernel.asm.o ${BIN_DIR}/boot.lst
)

# 合并 boot.bin 和 kernel.bin 为 os.bin，并填充额外的 512 字节
add_custom_command(
    OUTPUT ${OS_BIN}
    COMMAND ${CMAKE_COMMAND} -E rm -f ${OS_BIN}  # 删除旧 os.bin
    COMMAND dd if=${BOOT_BIN} of=${OS_BIN} bs=512 count=1
    COMMAND dd if=${KERNEL_BIN} of=${OS_BIN} bs=512 seek=1 conv=notrunc
    COMMAND dd if=/dev/zero bs=512 count=100 >> ${OS_BIN}
    DEPENDS ${BOOT_BIN} ${KERNEL_BIN}
    COMMENT "Merging boot.bin and kernel.bin into os.bin with padding"
)

# 默认目标：生成 os.bin
add_custom_target(
    all
    DEPENDS ${OS_BIN}
)
# 添加清理目标
add_custom_target(
    clean
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${BIN_DIR}/* ${BUILD_DIR}/*
    COMMENT "Cleaning up build files"
)

