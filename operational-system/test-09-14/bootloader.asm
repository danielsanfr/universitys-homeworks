; bootloader.asm

jmp main

%include "clear.asm"
%include "print.asm"
%include "set_pos.asm"

main:
    ; mov ax, 0 ; Para que serve esse ax
    mov ax, 0x07c0
    mov ds, ax

    call clear

    push $2
    push $1
    call set_pos
    push my
    call print

    push $3
    push $1
    call set_pos
    push load
    call print

    ; Carrega kernel
    mov ah, 0x02
    mov al, 0x02
    mov ch, 0x00
    mov cl, 0x02
    mov dh, 0x00
    mov dl, 0x00

    mov bx, 0x7E0
    mov es, bx
    mov bx, 0x0

    int 13h

    ; Desvia para o kernel
    ;cli
    ;hlt
    jmp 0x000:0x7E00

    my db 'Meu bootloader', 0
    load db 'Carregando kernel...', 0
    times 510-($-$$) db 0
    db 0x55
    db 0xAA
	
kernel:
    call clear
    push $8
    push $20
    call set_pos
    push msg
    call print

    jmp hang

hang:
    jmp hang
    msg db 'Meu SO', 0
