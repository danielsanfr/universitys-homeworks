    ; xchg bx, bx

    call load_kernel
    xchg bx, bx

    cli

    call load_gdt
    xchg bx, bx

    call switch_protected_mode
    xchg bx, bx

    ; sti

    jmp 0x08:0x8000 
	
load_kernel:
    push bp
    mov bp, sp

    mov ah, 0x02 ; ler do disco
    mov al, 0x02 ; ler 2 setores
    mov ch, 0x00 ; floppy so tem um cilindro.
    mov cl, 0x02 ; segundo setor
    mov dh, 0x00 ; face de cima
    mov dl, 0x00 ; primeiro floppy

    mov bx, 0x800
    mov es, bx ; ES:BX - 512 bytes apos o bootloader
    mov bx, 0x00  ;

    int 13h

    leave
    ret

load_gdt:
    push bp
    mov bp, sp

    ; carregando gdt
    mov ax, 0x7c0
    mov ds, ax

    lgdt [gdt_ptr]

    leave
    ret
	
switch_protected_mode:
    push bp
    mov bp, sp

    ; habilitar o modo protegido.
    mov eax, cr0
    or eax, 1
    mov cr0, eax

    leave
    ret

gdt_ptr:
    dw 24
    dd 0x7c00 + gdt

gdt:
    db 0, 0, 0, 0, 0, 0, 0, 0 			  ; null segment
    db 0xff, 0xff, 0, 0, 0, 0x9A, 0xCF, 0 ; code segment
    db 0xff, 0xff, 0, 0, 0, 0x92, 0xCF, 0 ; data segment

times 510-($-$$) db 0
db 0x55
db 0xAA
