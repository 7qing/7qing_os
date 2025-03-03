.section .text

.global insb
.global insw
.global outb
.global outw

insb:
    push %rbp
    mov %rsp, %rbp

    mov %di, %dx      # 将 port (unsigned short) 移动到 dx
    xor %eax, %eax     
    in %dx, %al       

    pop %rbp
    ret

insw:
    push %rbp
    mov %rsp, %rbp

    xor %eax, %eax    
    mov %edi, %edx
    in %dx, %ax 
    
    pop %rbp
    ret

outb:
    push %rbp
    mov %rsp, %rbp

    mov %esi, %eax    
    mov %edi, %edx
    out %al, %dx 
    
    pop %rbp
    ret

outw:
    push %rbp
    mov %rsp, %rbp

    mov %esi, %eax    
    mov %edi, %edx
    out %ax, %dx 
    
    pop %rbp
    ret