
bits 32 	;32-bit Protected Mode

;carrega uma idt a partir do parâmetro, que é o ponteiro da mesma
global idt_load
idt_load:
    
    push ebp
    mov ebp, esp

    ;Lembrando que na passagem de parametros a captura aqui é inversamente da passagem, antes da call

    mov eax, [ebp+8]  ; parâmetro que mostra o ponteiro da gdt a ser carregada
    
    ;xchg bx, bx	      ;ponteiro do bochs
    
    lidt [eax]        ; carrega a IDT com o nosso ponteiro passado no parametro
    
    leave
    ret               ; returning!

