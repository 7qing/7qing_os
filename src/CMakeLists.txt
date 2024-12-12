# src/CMakeLists.txt

# 添加子目录
add_subdirectory(boot)
add_subdirectory(kernel)

# 定义虚拟目标，确保 src 的构建包含 boot 和 kernel
add_custom_target(
    all_src
    DEPENDS ${BIN_DIR}/boot.bin ${BUILD_DIR}/kernel.asm.o
)
