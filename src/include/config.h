#ifndef INCLUDE_CONFIG__H__
#define INCLUDE_CONFIG__H__

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define SEVEN_QING_OS_TOTAL_INTRRUPTS 512

// 100Mb
#define SEVEN_QING_OS_HEAP_SIZE_BYTES 104857600
#define SEVEN_QING_OS_BLOCK_SIZE 4096
#define SEVEN_QING_OS_HEAP_ADDRESS 0x01000000
#define SEVEN_QING_OS_HEAP_TABLE_ADDRESS 0x00007E00
#endif
