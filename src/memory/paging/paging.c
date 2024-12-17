#include "paging.h"

#include "memory/heap/kheap.h"

struct paging_4gb_chunk* paging_new_4gb(uint8_t flags) {
    uint32_t* directory =
        kzalloc(sizeof(uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE);
    int offset = 0;
    for (int i = 0; i < PAGING_TOTAL_ENTRIES_PER_TABLE; i++) {
        uint32_t* entry =
            kzalloc(sizeof(uint32_t) * PAGING_TOTAL_ENTRIES_PER_TABLE);
        for (int j = 0; j < PAGING_TOTAL_ENTRIES_PER_TABLE; j++) {
            entry[j] = (offset + j * PAGING_PAGE_SIZE) | flags;
        }
        offset += (PAGING_TOTAL_ENTRIES_PER_TABLE * PAGING_PAGE_SIZE);
    }
}