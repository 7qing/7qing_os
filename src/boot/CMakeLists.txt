# src/boot/CMakeLists.txt

# 编译引导加载程序 boot.bin
add_custom_command(
    OUTPUT ${BIN_DIR}/boot.bin
    COMMAND ${NASM_EXECUTABLE} -f bin ${CMAKE_CURRENT_SOURCE_DIR}/boot.asm -o ${BIN_DIR}/boot.bin -l ${BIN_DIR}/boot.lst
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/boot.asm
    COMMENT "Building boot.bin"
)

# 添加目标
add_custom_target(
    boot ALL
    DEPENDS ${BIN_DIR}/boot.bin ${BIN_DIR}/boot.lst
)
