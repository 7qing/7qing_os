#ifndef KHEAP__H__
#define KHEAP__H__

void kheap_init();
void *kmalloc(size_t size);
void kfree(void *ptr);
void *kzalloc(size_t size);
#endif