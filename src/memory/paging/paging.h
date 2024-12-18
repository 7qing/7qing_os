/*
 * @Author: git.exe config user.name && error: git config user.email & please
 * set dead value or install git
 * @Date: 2024-12-17 19:22:26
 * @LastEditors: error: error: git config user.name & please set dead value or
 * install git && error: git config user.email & please set dead value or
 * install git & please set dead value or install git
 * @LastEditTime: 2024-12-18 20:55:13
 * @FilePath: /7qing_os/src/memory/paging/paging.h
 * @Description:
 *
 * Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#ifndef PAGING__H__
#define PAGING__H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PAGING_CACHE_DISABLED 0b00010000
#define PAGING_WRITE_THROUGH 0b00001000
#define PAGING_ACCESS_FROM_ALL 0b00000100
#define PAGING_IS_WRITEABLE 0b00000010
#define PAGING_IS_PRESENT 0b00000001

#define PAGING_PAGE_SIZE 4096
#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024

struct paging_4gb_chunk {
    /* data */
    uint32_t* directory_entry;
};

struct paging_4gb_chunk* paging_new_4gb(uint8_t flags);
void enable_paging();
void paging_switch(uint32_t* directory);
uint32_t* paging_4gb_chunk_get_directory(struct paging_4gb_chunk* chunk);
int paging_set(uint32_t* directory, void* virt, uint32_t val);
bool paging_is_aligned(void* addr);
#endif