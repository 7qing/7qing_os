#include "idt.h"

#include "include/config.h"

struct idt_desc idt_descriptors[SEVEN_QING_OS_TOTAL_INTRRUPTS];
struct idtr_desc idtr_descriptors;

void idt_init() {}