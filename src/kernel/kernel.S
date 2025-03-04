.section .text
.global reload_pml4
reload_pml4:
    push %ebp
    mov %esp, %ebp

    push %rax

    mov %cr3, %rax
    mov %rax, %cr3

    pop %rax
    pop %ebp

    ret

.section .text
.global memset
memset:
    push %ebp
    mov %esp, %ebp

    test    %rdx, %rdx
    jz      .done
   
    rep     stosb        

.done:
    pop %ebp
    ret


