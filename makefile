# 目标目录
TARGET_DIR := target/x86_64/iso/boot
# 定义目录
SRC_DIR := src
BUILD_DIR := ./build
BIN_DIR := ./bin
# 头文件路径
INCLUDES := -I $(SRC_DIR)/include 

# 编译器
CC := gcc
AS := gcc
NASM := nasm

# 编译选项 (C 编译) 
CFLAGS := -m64 --pipe -ffreestanding -nostdlib -fno-pie -fno-stack-protector -mcmodel=large -fno-asynchronous-unwind-tables

# 链接选项 (链接) 
LDFLAGS := -nostdlib -z max-page-size=0x1000 -Wl,--build-id=none -static

# 链接器脚本，指定链接器使用的脚本文件
LINKER_SCRIPT := $(SRC_DIR)/linker.ld

# 最终输出文件，指定链接器生成的最终可执行文件名
KERNEL_BIN := $(BIN_DIR)/kernel.bin
# 目标输出文件，指定最终输出文件要复制到的目标路径
OS_BIN := $(TARGET_DIR)/kernel.bin

OBJS := ./build/boot/bootstrap.o ./build/boot/entry64.o ./build/kernel/kernel.o
all: $(OS_BIN)
	
$(OS_BIN): $(KERNEL_BIN)
	@echo "[CP]kernel.bin -> $(OS_BIN)"
	rm -f $(OS_BIN)
	cp $< $@

$(KERNEL_BIN): $(OBJS)
	@echo "[LINK]kernel.bin"
	$(CC) -T $(LINKER_SCRIPT) -o $@ $(LDFLAGS) $(OBJS)

./build/boot/bootstrap.o: ./src/boot/bootstrap.S
	@echo "[AS] $< -> $@"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/boot/bootstrap.S -o $(BUILD_DIR)/boot/bootstrap.o
	

./build/boot/entry64.o: ./src/boot/entry64.S
	@echo "[AS] $< -> $@"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/boot/entry64.S -o $(BUILD_DIR)/boot/entry64.o

./build/kernel/kernel.o: ./src/kernel/kernel.c
	@echo "[CC] $< -> $@"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_DIR)/kernel/kernel.c -o $(BUILD_DIR)/kernel/kernel.o

clean:
	rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*
	








