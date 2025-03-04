/*
 * @Author: Yan Yixin 88801828+7qing@users.noreply.github.com
 * @Date: 2025-02-23 19:50:26
 * @LastEditors: Yan Yixin 88801828+7qing@users.noreply.github.com
 * @LastEditTime: 2025-03-04 18:12:13
 * @FilePath: /v2_7qing_os/src/memory/map.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "memory/map.h"
#include <stdint.h>
#include <stdbool.h>

#define map_pagemap(addr) \
    map_pageframe_to((uint64_t)addr, (uint64_t)addr, false, true, MEMM_PAGE_SIZE_4K);

