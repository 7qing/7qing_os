# 目标目录，指定最终输出文件要复制到的目录
TARGET_DIR := target/x86_64/iso/boot
# 定义目录
SRC_DIR := src
ARCH_DIR := $(SRC_DIR)/arch/x86
BUILD_DIR := ./build
BIN_DIR := ./bin
# 头文件路径
INCLUDES := -I $(SRC_DIR)/include 

# 编译器
CC := gcc
AS := gcc
NASM := nasm

# 编译选项 (C 编译) 
CFLAGS := -m64 -ffreestanding -z max-page-size=0x1000 -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -std=gnu99 -O2 -Wall -Wextra

# 链接选项 (链接) 
LDFLAGS := -ffreestanding -nostdlib -lgcc

# 链接器脚本，指定链接器使用的脚本文件
LINKER_SCRIPT := $(SRC_DIR)/linker.lds

# 最终输出文件，指定链接器生成的最终可执行文件名
KERNEL_BIN := $(BIN_DIR)/kernel.bin
# 目标输出文件，指定最终输出文件要复制到的目标路径
OS_BIN := $(TARGET_DIR)/kernel.bin

# 自动查找文件
C_SOURCES := $(shell find $(SRC_DIR) -not -path "$(SRC_DIR)/boot*" -name "*.c")
ASM_SOURCES := $(shell find $(SRC_DIR) -not -path "$(SRC_DIR)/boot*" -name "*.S")

# 生成对象文件
ASM_OBJS := $(patsubst $(SRC_DIR)/%.S, $(BUILD_DIR)/%.o, $(ASM_FILES))
C_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))
NASM_OBJS := $(BUILD_DIR)/boot/entry32.o

OBJS := $(C_OBJS) $(ASM_OBJS) 

all: $(OS_BIN)

$(OS_BIN): $(KERNEL_BIN)
	@echo "[CP]kernel.bin -> $(OS_BIN)"
	rm -f $(OS_BIN)
	cp $< $@

$(KERNEL_BIN):	$(BUILD_DIR) $(OBJS)
	@echo "[LINK]kernel.bin"
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(LDFLAGS) $(OBJS) $(NASM_OBJS)

	
# 编译 C 代码
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[CC] $< -> $@"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 编译汇编
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S
	@echo "[AS] $< -> $@"
	mkdir -p $(dir $@)
	$(AS) $(INCLUDES)  -c $< -o $@

# 编译 NASM 汇编
$(NASM_OBJS):
	mkdir -p $(BUILD_DIR)/boot
	$(NASM) -f elf32 $(NASM_SOURCES) -o $(BUILD_DIR)/boot/entry32.o $(SRC_DIR)/boot/entry32.S
	objcopy -I elf32-i386 -O elf64-x86-64 $(BUILD_DIR)/boot/entry32.o $(BUILD_DIR)/boot/entry32.o
	# $(NASM) -f elf64 $(NASM_SOURCES) -o $(BUILD_DIR)/boot/entry64.o $(SRC_DIR)/boot/entry64.S

clean:









