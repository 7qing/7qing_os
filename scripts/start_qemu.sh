#!/bin/sh
###
 # @Author: 7qing 3454523412@qq.com
 # @Date: 2025-02-19 03:40:47
 # @LastEditors: Yan Yixin 88801828+7qing@users.noreply.github.com
 # @LastEditTime: 2025-02-23 07:34:20
 # @FilePath: /v2_7qing_os/srcipts/start_qemu.sh
 # @Description: 编译一个镜像，启动脚本
### 

# comp
grub-mkrescue /usr/lib/grub/x86_64-efi -o kernel.iso target/x86_64/iso

# start qemu
qemu-system-x86_64 \
        -bios /usr/share/ovmf/OVMF.fd \
        -cpu kvm64,+smep,+smap \
        -smp sockets=1,dies=1,cores=4,threads=2 \
        -m 4G \
        --machine q35 \
        -drive file=./kernel.iso,format=raw,index=0,media=disk \
        -s  # 启动gdb调试