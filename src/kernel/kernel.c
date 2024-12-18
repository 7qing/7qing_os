#include "kernel.h"

#include "idt/idt.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"

struct paging_4gb_chunk* kernel_chunk = 0;

void kernel_main() {
    kheap_init();

    idt_init();

    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT |
                                  PAGING_ACCESS_FROM_ALL);
    paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));
    enable_paging();

    enable_interrupts();
}