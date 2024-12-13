section .asm

extern int21_handler

global idt_load
global int21h

idt_load:
    push ebp
    mov ebp, esp

    mov ebx, [ebp+8]
    lidt [ebx]
    
    pop ebp
    ret

int21h:
    cli
    pushad
    call int21_handler
    popad
    sti
    iret
