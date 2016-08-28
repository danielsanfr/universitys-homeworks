; set_pos.asm

set_pos:
    push bp
    mov bp, sp

    ; Faz algo que eu nao sei
    mov ah, 0x02
    mov bh, 0
    ; =======================

    mov dh, [bp + 6]
    mov dl, [bp + 4]
    int 10h

    leave
    ret
