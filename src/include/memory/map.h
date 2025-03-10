/*
 * @Author: Yan Yixin 88801828+7qing@users.noreply.github.com
 * @Date: 2025-03-04 16:29:31
 * @LastEditors: Yan Yixin 88801828+7qing@users.noreply.github.com
 * @LastEditTime: 2025-03-04 18:07:31
 * @FilePath: /7qing_os/src/include/memory/map.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef INCLUDE_MEMORY_H
#define INCLUDE_MEMORY_H

#include <stdint.h>
#include <stddef.h>

/* 页大小，以MEMM_PAGE_SIZE为单位 */
#define MEMM_PAGE_SIZE 4096
typedef enum __memm_page_size {
    MEMM_PAGE_SIZE_4K = 1,       // 1个4KB页大小
    MEMM_PAGE_SIZE_2M = 512,     // 512个4KB页大小
    MEMM_PAGE_SIZE_1G = 262144,  // 262144个4KB页大小
} memm_page_size;

extern uint64_t PML4[512];

#define MEMM_PAGE_TABLE_FLAGS_AREA ((uint64_t)0xfff)
extern void memset(void *s, int c, size_t n);
/* 页对齐掩码 */
#define MEMM_4K_ALIGN_MASK ((uint64_t)0xfff)
#define MEMM_2M_ALIGN_MASK ((uint64_t)0x1fffff)
#define MEMM_1G_ALIGN_MASK ((uint64_t)0x3fffffff)

/* 页表项属性FLAGS */
#define MEMM_ENTRY_FLAG_PRESENT ((uint64_t)1)
#define MEMM_ENTRY_FLAG_WRITE ((uint64_t)1 << 1)
#define MEMM_ENTRY_FLAG_USER ((uint64_t)1 << 2)
#define MEMM_ENTRY_FLAG_PWT ((uint64_t)1 << 3)
#define MEMM_ENTRY_FLAG_PCD ((uint64_t)1 << 4)
#define MEMM_ENTRY_FLAG_ACCECED ((uint64_t)1 << 5)
#define MEMM_ENTRY_FLAG_DIRTY ((uint64_t)1 << 6)
#define MEMM_ENTRY_FLAG_PS ((uint64_t)1 << 7)
#define MEMM_ENTRY_FLAG_GLOBAL ((uint64_t)1 << 8)
#define MEMM_ENTRY_FLAG_PAT ((uint64_t)1 << 12)
#define MEMM_PTE_ENTRY_FLAG_PAT ((uint64_t)1 << 7)
#define MEMM_ENTRY_FLAG_XD ((uint64_t)1 << 63)
#define memm_entry_flag_get(entry, flag) ((entry & flag) ? true : false)

/* 页表（大型页）项地址域掩码 */
#define MEMM_ENTRY_ADDRESS_MASK ((uint64_t)0x000ffffffffff000)
#define MEMM_BP_ENTRY_ADDRESS_MASK ((uint64_t)0x000fffffffffe000)
#define memm_entry_get_address(entry)                          \
    ((entry) & (memm_entry_flag_get(entry, MEMM_ENTRY_FLAG_PS) \
                    ? MEMM_BP_ENTRY_ADDRESS_MASK               \
                    : MEMM_ENTRY_ADDRESS_MASK))

/* 线性地址表项索引或页内偏移掩码 */
#define MEMM_LA_PML4EI_MASK ((uint64_t)0x0000ff8000000000)
#define MEMM_LA_PDPTEI_MASK ((uint64_t)0x0000007fc0000000)
#define MEMM_LA_PDEI_MASK ((uint64_t)0x000000003fe00000)
#define MEMM_LA_PEI_MASK ((uint64_t)0x00000000001ff000)

#define MEMM_LA_1GB_PAGE_OFFSET_MASK ((uint64_t)0x000000003fffffff)
#define MEMM_LA_2MB_PAGE_OFFSET_MASK ((uint64_t)0x00000000001fffff)
#define MEMM_LA_4KB_PAGE_OFFSET_MASK ((uint64_t)0x0000000000000fff)

/* 线性地址表项索引偏移位数 */
#define MEMM_LA_PML4EI_OFFSET (39)
#define MEMM_LA_PDPTEI_OFFSET (30)
#define MEMM_LA_PDEI_OFFSET (21)
#define MEMM_LA_PEI_OFFSET (12)

/* 获取线性地址中某个表项索引以及获取页内偏移 */
#define MEMM_LA_PML4EI
#define MEMM_LA_PDPTEI
#define MEMM_LA_PDEI
#define MEMM_LA_PEI
#define memm_la_get_entry_index(addr, entry) \
    (((addr) & (entry##_MASK)) >> (entry##_OFFSET))

#define MEMM_LA_1GB_PAGE_OFFSET
#define MEMM_LA_2MB_PAGE_OFFSET
#define MEMM_LA_4KB_PAGE_OFFSET
#define memm_la_get_offset(addr, page_type) ((addr) & (page_type##_MASK))

#define is_user_address(addr) (((addr) > 0xffff7fffffffffff) ? true : false)

#define is_cannonical(addr)                                              \
    (((addr) < 0x0000800000000000 || (addr) > 0xffff7fffffffffff) ? true \
                                                                  : false)

#define memm_get_page_align(addr)                                   \
    (is_aligned(addr, MEMM_PAGE_SIZE_1G)                            \
         ? MEMM_PAGE_SIZE_1G                                        \
         : (is_aligned(addr, MEMM_PAGE_SIZE_2M) ? MEMM_PAGE_SIZE_2M \
                                                : MEMM_PAGE_SIZE_4K))

#endif
