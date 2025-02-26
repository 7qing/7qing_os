#include "idt.h"

#include "include/config.h"
#include "io/io.h"
#include "memory/memory.h"

struct idt_desc idt_descriptors[SEVEN_QING_OS_TOTAL_INTRRUPTS];
struct idtr_desc idtr_descriptors;

extern void idt_load(struct idtr_desc *idt_ptr);
extern void int21h();

void int21h_handler() {
    print("keybroad pressed\n");
    outb(0x20, 0x20);
}
void idt_zero() { print("Divide by 0 error\n"); }

void idt_set(int interrupts_no, void *address) {
    struct idt_desc *ptr = &idt_descriptors[interrupts_no];
    ptr->offset_1 = (uint32_t)address & 0x0000ffff;
    ptr->selector = KERNEL_CODE_SELECTOR;
    ptr->zero = 0x00;
    ptr->offset_2 = (uint32_t)address >> 16;
}

void idt_init() {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptors.limit = size(idtr_descriptors) - 1;
    idtr_descriptors.base = (uint32_t)idt_descriptors;

    // set
    idt_set(0, idt_zero);
    idt_set(0x21, int21h);

    // load
    idt_load(&idtr_descriptors);
}