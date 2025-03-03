#define ASM_FILE 1
#include<boot/multiboot2.h>

.section .boot.loader.header
.align 8
multiboot_header:
        .long   MULTIBOOT2_HEADER_MAGIC
        .long   0
        .long   multiboot_header_end - multiboot_header
        .long   -(MULTIBOOT2_HEADER_MAGIC + multiboot_header_end - multiboot_header)

tag_entry:
    .align 8
    .short MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS
    .short 0
    .long 12
    .long bootstrap

tag_frame_buffer:
    .align 8
    .short MULTIBOOT_HEADER_TAG_FRAMEBUFFER
    .short 0
    .long 20
    .long 1024
    .long 768
    .long 32
tag_information_request:
    .align 8
    .short MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST
    .short tag_information_request_tag_end - tag_information_request
    .long 4
    .long 1
    .long 8
    .long 12
tag_information_request_tag_end:
tags_end:
    .align 8
    .short  MULTIBOOT_HEADER_TAG_END
    .short  0
    .long   8
multiboot_header_end:


.section .boot.loader.text
.code32
.align 0x0008
.global bootstrap
.extern init64
bootstrap:
    cli
    
    # Disable paging (UEFI may turn it on)
    movl %cr0, %eax                                  # Set the A-register to control register 0.
    andl $0x7FFFFFFF, %eax                           # Clear the PG-bit, which is bit 31. 
    movl %eax, %cr0                                  # Set control register 0 to the A-register.

    #  early paging
    # 设置 PML4 的第 0 项
    movl $boot_PDPT0, %eax   # PDPT0
    addl $0x003, %eax
    movl $boot_PML4, %edi   # PML4
    movl %eax, (%edi)      # 写入 PML4
    addl $4, %edi
    movl $0, (%edi)        # 清空高 32 位
    # 设置 PDPT0 的第 0 项
    movl $boot_PD0, %eax   # PD0
    addl $0x003, %eax
    movl $boot_PDPT0, %edi   # PDPT0
    movl %eax, (%edi)      # 写入 PDPT0
    addl $4, %edi
    movl $0, (%edi)        # 清空高 32 位

    # 设置 PD0 中的 PDE
    movl $64, %ecx         # 循环次数
    movl $0, %eax          # 初始化 eax
    movl $0x103000, %edi   # PD0
    .SetEntry:
        movl %eax, %edx
        addl $0x183, %edx
        movl %edx, (%edi)
        addl $0x400000, %eax   # 2MB
        addl $4, %edi
        movl $0, (%edi)
        addl $4, %edi
        loop .SetEntry  
    
    # Set the PAE enable bit in CR4
    movl %cr4, %eax             # Set the A-register to control register 4.
    orl $0x20, %eax              # Set the PAE-bit, which is the 6th bit (bit 5). (1 << 5 = 32 = 0x20)
    movl %eax, %cr4             # Set control register 4 to the A-register.

    # Load CR3 with the physical address of the PML4 (Level 4 Page Map)
    movl     $boot_PML4, %eax  # PML4
    movl     %eax, %cr3

    # Enable long mode by setting the LME flag (bit 8) in MSR 0xC0000080 (aka EFER)
    movl $0xC0000080, %ecx      # Set the C-register to 0xC0000080, which is the EFER MSR.
    rdmsr                        # Read from the model-specific register.
    orl $0x100, %eax             # Set the LM-bit which is the 9th bit (bit 8). (1 << 8 = 256 = 0x100)
    wrmsr                        # Write to the model-specific register.

    # Enable paging
    movl %cr0, %eax             # Set the A-register to control register 0.
    orl $0x80000000, %eax        # Set the PG-bit (31st bit) .
    movl %eax, %cr0             # Set control register 0 to the A-register.


    # set up GDT
    mov     $gdt64_ptr, %eax
    lgdt    0(%eax)

    mov $0x10 , %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    # go longmode 
    jmp $0x8, $init64 

halt:
    hlt
    jmp halt

.section .boot.loader.data
     .align 0x1000

    .globl boot_stack, boot_stack_top

    #
    # When the system is booted under legacy BIOS, there's no stack
    # So we reserve a page there as a temporary stack for booting
    #
    boot_stack:
        .space 0x1000
    boot_stack_top:
        
    .align 0x1000
    .globl boot_PML4,boot_PDPT0,boot_PD0
    boot_PML4:
    .space 512 * 8       # 使用 .space 保留空间 (512 * 8 字节)

    boot_PDPT0:
    .space 512 * 8

    boot_PD0:
    .space 512 * 8
    
    # global segment descriptor table
    .align 0x1000   # it should be aligned to page
    .globl gdt64, gdt64_ptr
    gdt64:
        .quad 0 # first one must be zero
    gdt64_kernel_code_segment:
        .quad 0x0020980000000000 # exec/read
    gdt64_kernel_data_segment:
        .quad 0x0000920000000000 # read/write
    gdt64_user_code_segment:
        .quad 0x0020f80000000000 # exec/read
    gdt64_user_data_segment:
        .quad 0x0000f20000000000 # read/write
    
    gdt64_ptr:
        .short gdt64_ptr - gdt64 - 1    # GDT limit
        .long gdt64                     # GDT Addr