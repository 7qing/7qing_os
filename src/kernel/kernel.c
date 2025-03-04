/*
 * @Author: Yan Yixin 88801828+7qing@users.noreply.github.com
 * @Date: 2025-02-22 14:07:07
 * @LastEditors: Yan Yixin 88801828+7qing@users.noreply.github.com
 * @LastEditTime: 2025-03-04 19:40:41
 * @FilePath: /v2_7qing_os/src/kernel/main.c
 * @Description: 这个是c语言启动的入口
 */


#include <stddef.h>
#include <stdint.h>
#include "memory/map.h"
#include "boot/multiboot2.h"

static uint32_t *framebuffer_base; /* 32 bit color */
static uint32_t framebuffer_width;
static uint32_t framebuffer_height;


static void* boot_get_frame_buffer(multiboot_uint8_t *mbi)
{
    struct multiboot_tag_framebuffer *fb_info = NULL;
    struct multiboot_tag *tag = (struct multiboot_tag *) (mbi + 8);

    /* find framebuffer tag */
    if (tag == NULL) {
        return NULL;
    }

    while (tag->type != MULTIBOOT_TAG_TYPE_END) {
        if (tag->type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER) {
            fb_info = (struct multiboot_tag_framebuffer*) tag;
            break;
        }

        tag = (struct multiboot_tag *) \
              ((multiboot_uint8_t *) tag + ((tag->size + 7) & ~7));
    }

    if (fb_info == NULL) {
        return NULL;
    }

    framebuffer_base = (uint32_t*) fb_info->common.framebuffer_addr;
    framebuffer_height = fb_info->common.framebuffer_height;
    framebuffer_width = fb_info->common.framebuffer_width;
    
    return fb_info;
}

extern void kernel_main(multiboot_uint8_t *mbi) {
  void *addr;
  addr = boot_get_frame_buffer(mbi);
  
  while(1);
}