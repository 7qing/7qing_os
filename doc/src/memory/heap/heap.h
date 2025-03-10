#ifndef HEAP__H__
#define HEAP__H__

#include <stddef.h>
#include <stdint.h>

#include "config.h"

#define HEAP_BLOCK_TABLE_ENTRY_TAKEN 0x01
#define HEAP_BLOCK_TABLE_ENTRY_FREE 0x00

#define HEAP_BLOCK_HAS_NEXT 0b10000000
#define HEAP_BLOCK_IS_FIRST 0b01000000

typedef unsigned char HEAP_BLOCK_TABLE_ENTRY;

struct heap_table {
    /* data */
    HEAP_BLOCK_TABLE_ENTRY* entries;
    size_t total;
};

struct heap {
    /* data */
    struct heap_table* table;

    // start address of the data pool
    void* saddr;
};
int heap_create(struct heap* heap, void* ptr, void* end,
                struct heap_table* table);

void* heap_malloc(struct heap* heap, size_t size);

void* heap_free(struct heap* heap, void* ptr);

#endif