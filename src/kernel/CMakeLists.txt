# 编译内核 kernel.asm.o
add_custom_command(
    OUTPUT ${BUILD_DIR}/kernel.asm.o
    COMMAND ${NASM_EXECUTABLE} -f elf ${CMAKE_CURRENT_SOURCE_DIR}/kernel.asm -o ${BUILD_DIR}/kernel.asm.o
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/kernel.asm
    COMMENT "Building kernel.asm.o"
)

# 添加目标
add_custom_target(
    kernel ALL
    DEPENDS ${BUILD_DIR}/kernel.asm.o
)