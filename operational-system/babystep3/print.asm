bios_print:
    lodsb
    or al, al ; zero=end or str
    jz done   ; get out
    mov ah, 0x0E
    int 0x10
    jmp bios_print
