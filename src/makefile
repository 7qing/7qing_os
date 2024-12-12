# 定义文件路径和变量
BIN_DIR = ./bin
BUILD_DIR = ./build
SRC_DIR = ./src

BOOT_SRC = $(SRC_DIR)/boot/boot.asm
BOOT_BIN = $(BIN_DIR)/boot.bin

KERNEL_SRC = $(SRC_DIR)/kernel.c
KERNEL_ASM_SRC = $(SRC_DIR)/kernel.asm
KERNEL_BIN = $(BIN_DIR)/kernel.bin
KERNEL_ASM_OBJ = $(BUILD_DIR)/kernel.asm.o
KERNEL_FULL_OBJ = $(BUILD_DIR)/kernelfull.o

OS_BIN = $(BIN_DIR)/os.bin
LINKER_SCRIPT = $(SRC_DIR)/linker.ld

# 编译器和链接器
NASM = nasm
LD = i686-elf-ld
GCC = i686-elf-gcc

# GCC 和链接器标志
CFLAGS = -pipe -ffreestanding -nostdlib -fno-pie -fno-stack-protector -mcmodel=large -fno-asynchronous-unwind-tables
LDFLAGS = -T $(LINKER_SCRIPT)

# 汇编器标志
NASM_BOOT_FLAGS = -f bin
NASM_KERNEL_FLAGS = -f elf

# 目标
all: $(OS_BIN)

# 构建 OS 镜像
$(OS_BIN): $(BOOT_BIN) $(KERNEL_BIN)
	@echo "[LINK] Creating OS binary: $(OS_BIN)"
	rm -f $(OS_BIN)
	dd if=$(BOOT_BIN) >> $(OS_BIN)
	dd if=$(KERNEL_BIN) >> $(OS_BIN)
	dd if=/dev/zero bs=512 count=100 >> $(OS_BIN)

# 构建内核二进制文件
$(KERNEL_BIN): $(KERNEL_ASM_OBJ)
	@echo "[LINK] Linking kernel: $(KERNEL_BIN)"
	$(LD) -r -o $(KERNEL_FULL_OBJ) $(KERNEL_ASM_OBJ)
	$(GCC) $(LDFLAGS) -o $(KERNEL_BIN) $(CFLAGS) $(KERNEL_FULL_OBJ)

# 构建内核汇编目标文件
$(KERNEL_ASM_OBJ): $(KERNEL_ASM_SRC)
	@echo "[ASM] Compiling kernel ASM: $(KERNEL_ASM_OBJ)"
	$(NASM) $(NASM_KERNEL_FLAGS) $(KERNEL_ASM_SRC) -o $(KERNEL_ASM_OBJ)

# 构建引导程序
$(BOOT_BIN): $(BOOT_SRC)
	@echo "[ASM] Compiling bootloader: $(BOOT_BIN)"
	$(NASM) $(NASM_BOOT_FLAGS) $(BOOT_SRC) -o $(BOOT_BIN)

# 清理目标
clean:
	@echo "[CLEAN] Removing build artifacts"
	rm -rf $(BIN_DIR)/*
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
