/*
 * @Author: Yan Yixin 88801828+7qing@users.noreply.github.com
 * @Date: 2025-02-22 14:07:07
 * @LastEditors: Yan Yixin 88801828+7qing@users.noreply.github.com
 * @LastEditTime: 2025-02-23 09:20:29
 * @FilePath: /v2_7qing_os/src/kernel/main.c
 * @Description: 这个是c语言启动的入口
 */

#include "boot/multiboot2.h"
#include <stddef.h>
#include <stdint.h>


/* frame buffer info */
static uint32_t *framebuffer_base; /* 32 bit color */
static uint32_t framebuffer_width;
static uint32_t framebuffer_height;





extern void kernel_main(unsigned int magic, multiboot_uint8_t *mbi) {
    while (1);
   
    
}





