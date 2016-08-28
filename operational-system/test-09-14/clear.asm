; clear.asm

clear:
    push bp
    mov bp, sp

    mov ah, 0x06
    mov al, 0
    mov bh, 11
    mov ch, 0
    mov cl, 0
    mov dh, 25
    mov dl, 80
    int 0x10

    leave
    ret
