#include "kheap.h"

#include "heap.h"
#include "include/config.h"
#include "kernel/kernel.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init() {
    int total_table_entries =
        SEVEN_QING_OS_HEAP_SIZE_BYTES / SEVEN_QING_OS_BLOCK_SIZE;
    kernel_heap_table.entries =
        (HEAP_BLOCK_TABLE_ENTRY *)SEVEN_QING_OS_HEAP_TABLE_ADDRESS;
    kernel_heap_table.total = total_table_entries;
    void *end =
        (void *)(SEVEN_QING_OS_HEAP_ADDRESS + SEVEN_QING_OS_HEAP_SIZE_BYTES);
    int res = heap_create(&kernel_heap, (void *)(SEVEN_QING_OS_HEAP_ADDRESS),
                          end, &kernel_heap_table);
    if (res < 0) {
        print("failed to create heap");
    }
}

void *kmalloc(size_t size) { return heap_malloc(&kernel_heap, size); }

void kfree(void *ptr) { heap_free(&kernel_heap, ptr); }