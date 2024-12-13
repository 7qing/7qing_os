[BITS 32]
global _start
extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

load32:
    mov ax, DATA_SEG 
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ;enables A20
    in al, 0x92
    or al, 2
    out 0x92, al

    ;remap the master pic
    mov al, 00010001b
    out 0x20, al ; master PIC

    mov al,0x20 
    out 0x21,al
    
    mov al, 00000001b
    out 0x21, al


    sti
    call kernel_main

    jmp $

times 512- ($ - $$) db 0