#ifndef IDT__H__
#define IDT__H__
#include <stdint.h>
struct idt_desc {
    /* data */
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_2;
} __attribute__((pack));

struct idtr_desc {
    /* data */
    uint16_t limit;
    uint32_t base;
} __attribute__((pack));

#endif