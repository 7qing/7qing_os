.section .text
.global reload_pml4
reload_pml4:
    push rax

    mov %cr3, %rax
    mov %rax, %cr3

    pop rax

    ret