.section .boot.loader.text
.align 8
.code64
.global init64
# .extern kernel_main
init64:
    endbr64
    cli

    mov $boot_stack_top, %rax
    mov %rax, %rsp
    mov %rax, %rbp
    mov %rbx, %rdi
    jmp kernel_main
    jmp .