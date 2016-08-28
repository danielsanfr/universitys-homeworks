; kernel.asm

jmp main

%include "clear.asm"
%include "print.asm"
%include "set_pos.asm"

main:
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
