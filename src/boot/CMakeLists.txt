# src/boot/CMakeLists.txt

# 添加汇编文件作为目标
set(NASM_FILE ${CMAKE_SOURCE_DIR}/src/boot/boot.asm)

set(BIN_OUTPUT ${CMAKE_BINARY_DIR}/boot.bin)
set(LST_OUTPUT ${CMAKE_BINARY_DIR}/boot.lst)

add_custom_command(
    OUTPUT ${BIN_OUTPUT} ${LST_OUTPUT}
    COMMAND nasm -f bin -o ${BIN_OUTPUT} -l ${LST_OUTPUT} ${NASM_FILE}
    COMMENT "Compiling ${NASM_FILE} with NASM"
)

add_custom_target(
    BootAsm ALL
    DEPENDS ${BIN_OUTPUT} ${LST_OUTPUT}
)