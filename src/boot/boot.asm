ORG 0x7c00
BITS 16

_start:
    jmp short start
    nop

times 33 db 0

start:
    jmp 0:step2

step2:
    cli     ;Clear Interrupts
    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti ; Enables Interrupts

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov  eax, cr0
    or eax, 0x1
    mov cr0, eax

; GDT
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code:  ;cs
    dw 0xffff
    dw 0
    dw 0
    db 0x9a
    db 11001111b
    db 0

; offset 0x10
gdt_data: ;ds ss es fs  gs
    dw 0xffff
    dw 0
    dw 0
    db 0x92
    db 11001111b
    db 0 

gdt_end:


gdt_descriptor:
    dw gdt_end- start -1
    dd gdt_start

    

print:
    .loop:
    lodsb
    or al, al
    jz .done
    mov ah, 0eh
    int 0x10
    jmp .loop
.done:
    ret

times 510- ($ - $$) db 0

db 0x55
db 0xAA
