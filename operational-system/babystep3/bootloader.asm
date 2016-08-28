; bootloader.asm

; This block is not necessary if you put print.asm code in this same file
jmp main

%include "print.asm"

main:
; =========================

[ORG 0x7c00]
    xor ax, ax ; make it zero
    mov ds, ax

    mov si, msg
    call bios_print

hang:
    jmp hang

msg   db 'Hello World', 13, 10, 0

; Here's the code of the file print.asm
 
done:
    ret
 
    times 510-($-$$) db 0
    db 0x55
    db 0xAA
