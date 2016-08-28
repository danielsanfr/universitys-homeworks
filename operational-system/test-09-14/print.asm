; print.asm

print:
    push bp
    mov bp, sp

    mov si, [bp + 4]

.loop:
    lodsb ; Carrega 1 byte ou palavra para o al, ax...
    or al, al ; zero=end or str
    jz done   ; get out
    ; Outra forma de comprar
    ; cmp al, 0
    ; je done
    ; ======================
    mov ah, 0x0E
    int 0x10
    jmp .loop

done:
    leave
    ret
