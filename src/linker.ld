OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(bootstrap)

SECTIONS
{
    /* boot loader will load the kernel there */
    . = 1M;
        __boot_start = .;

        /* ASM boot-state kernel */
        .boot.loader : {
            *(.boot.loader*)
        }
        . = ALIGN(4096);


        __boot_end = .;

        /* now we come to the REAL kernel */

        KERM_VADDR = 0xffffffff81000000;
        . = KERM_VADDR;
        /* we use AT() there to make it loaded on phys correctly */
        .text ALIGN(4096) : AT (ADDR (.text) - KERM_VADDR + __boot_end)
        {
                *(.text)
        }

        . = ALIGN(4096);

        .rodata ALIGN(4096) : AT (ADDR (.rodata) - KERM_VADDR + __boot_end)
        {
                *(.rodata)
        }

        . = ALIGN(4096);

        __roseg_end = .;

        .data ALIGN(4096) : AT (ADDR (.data) - KERM_VADDR + __boot_end)
        {
                *(.data)
        }

        . = ALIGN(4096);

        .bss ALIGN(4096) : AT (ADDR (.bss) - KERM_VADDR + __boot_end)
        {
                *(COMMON)
                *(.bss)
        }

        . = ALIGN(4096);

        __kernel_end = .;
        /DISCARD/ :
        {
                *(.comment)
        }
}