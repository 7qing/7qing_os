# 定义目录
SRC_DIR := ./src
BUILD_DIR := ./build
BIN_DIR := ./bin

BOOT_SRC := $(SRC_DIR)/boot/boot.asm
BOOT_BIN := $(BIN_DIR)/boot.bin

KERNEL_LDS := $(SRC_DIR)/kernel/linker.lds
KERNEL_BIN := $(BIN_DIR)/kernel.bin

# 包含路径
INCLUDE_DIRS := -I$(SRC_DIR)/include -I$(SRC_DIR)/idt -I$(SRC_DIR)/io -I$(SRC_DIR)/memory -I$(SRC_DIR)/kernel

# 工具链
NASM := nasm
LD := i686-elf-ld
GCC := i686-elf-gcc

# 编译标志
CFLAGS := -ffreestanding -nostdlib -fno-pie -fno-stack-protector $(INCLUDE_DIRS) -Wall -Wextra
NASM_BOOT_FLAGS := -f bin
NASM_OBJ_FLAGS := -f elf
LDFLAGS := -T $(KERNEL_LDS)

# 自动查找文件
ASM_FILES := $(shell find $(SRC_DIR) -name "*.asm" ! -name "boot.asm")
C_FILES := $(shell find $(SRC_DIR) -name "*.c")

# 生成对象文件
ASM_OBJS := $(patsubst $(SRC_DIR)/%.asm, $(BUILD_DIR)/%.o, $(ASM_FILES))
C_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(C_FILES))

# 最终 OS 镜像
OS_BIN := $(BIN_DIR)/os.bin

# 目标
all: $(OS_BIN)

# 构建 OS 镜像
$(OS_BIN): $(BOOT_BIN) $(KERNEL_BIN)
	@echo "[LINK] Combining bootloader and kernel into OS image: $(OS_BIN)"
	mkdir -p $(BIN_DIR)
	rm -f $(OS_BIN)
	dd if=$(BOOT_BIN) of=$(OS_BIN)
	dd if=$(KERNEL_BIN) >> $(OS_BIN)
	dd if=/dev/zero bs=512 count=100 >> $(OS_BIN)

# 编译引导程序
$(BOOT_BIN): $(BOOT_SRC)
	@echo "[ASM] Compiling bootloader: $(BOOT_BIN)"
	mkdir -p $(BIN_DIR)
	$(NASM) $(NASM_BOOT_FLAGS) $< -o $@

# 生成内核二进制文件
$(KERNEL_BIN): $(ASM_OBJS) $(C_OBJS)
	@echo "[LINK] Linking kernel: $(KERNEL_BIN)"
	mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $@ $(ASM_OBJS) $(C_OBJS)

# 汇编文件编译规则
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.asm
	@echo "[ASM] Compiling: $< -> $@"
	mkdir -p $(dir $@)
	$(NASM) $(NASM_OBJ_FLAGS) $< -o $@

# C 文件编译规则
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[GCC] Compiling: $< -> $@"
	mkdir -p $(dir $@)
	$(GCC) $(CFLAGS) -c $< -o $@

# 清理规则
clean:
	@echo "[CLEAN] Removing build and binary directories"
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
