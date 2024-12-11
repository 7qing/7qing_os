# src/CMakeLists.txt

# 添加内核子目录
add_subdirectory(kernel)

# 定义 kernel.asm
set(KERNEL_ASM ${CMAKE_SOURCE_DIR}/src/kernel/kernel.asm)

# 编译 kernel.asm
set(KERNEL_BIN ${CMAKE_BINARY_DIR}/kernel.bin)
add_custom_command(
    OUTPUT ${KERNEL_BIN}
    COMMAND nasm -f bin -o ${KERNEL_BIN} ${KERNEL_ASM}
    COMMENT "Compiling ${KERNEL_ASM} with NASM"
    DEPENDS ${KERNEL_ASM}
)

# 定义目标以确保 kernel.bin 生成
add_custom_target(kernel_target DEPENDS ${KERNEL_BIN})

# 将 kernel_target 作为构建依赖
# add_dependencies(nasm_target kernel_target)
