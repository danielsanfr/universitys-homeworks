;[ORG 0x7c00]

xor ax, ax
mov ds, ax

; limpar a tela
call cls

push 1
push 1
push meuBootloader
call print

push 2
push 1
push carregandoKernel
call print

;mov ah, 0x02	; 0x02 ler do
;mov al, 0x02	; ler 2 setores
;mov ch, 0x00	; floppy só tem um cilindro.
;mov cl, 0x02	; segundo setor
;mov dh, 0x00	; face de cima
;mov dl, 0x00	; primeiro floppy

;mov bx, 0x840
;mov es, bx		; ES:BX - 512 bytes após o bootloader
;mov bx, 0x0

;int 13h

; COMECO DA ATIVIDADE 2...

; Carregar o kernel
call carregar_kernel

;xchg bx, bx

; Carregar a GDT
call load_gdt

;xchg bx, bx

; Ir para o modo protegido
call modo_protegido

;xchg bx, bx
; Jump para o kernel
jmp 0x008:0x8400

carregar_kernel:
	push bp
	mov bp, sp
	
	mov ah, 0x02	; 0x02 ler do
	mov al, 0x02	; ler 2 setores
	mov ch, 0x00	; floppy só tem um cilindro.
	mov cl, 0x02	; segundo setor
	mov dh, 0x00	; face de cima
	mov dl, 0x00	; primeiro floppy
	
	mov bx, 0x840
	mov es, bx		; ES:BX - 512 bytes após o bootloader
	mov bx, 0x0
	
	int 13h
	
	leave
	ret
	
modo_protegido:
	push bp
	mov bp, sp
	
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	
	leave
	ret
	

cls:	; limpar a tela

	push bp
	mov bp, sp	
	
	mov ah, 06h
	mov al, 0
	mov bh, 0x0F
	mov ch, 0
	mov cl, 0
	mov dh, 25
	mov dl, 80
	
	int 10h
	
	; Mover o cursor
	push 0
	push 0
	call mover_cursor
	
	leave
	ret
	
mover_cursor:
	push bp
	mov bp, sp
	
	mov ah, 0x02
	mov dh, [bp+6]	; linha
	mov dl, [bp+4]	; coluna
	mov bh, 0
	
	int 10h
	
	leave
	ret

;---------------------------------------------
; Funcoes para printar na tela
;---------------------------------------------

print: ; print
	push bp
	mov bp, sp
	
	; Empilhar a linha e a coluna
	mov ax, [bp+8]
	push ax
	mov bx, [bp+6]
	push bx
	call mover_cursor
	
	; Pegar a string
	mov si, [bp+4]
	
	jmp print_loop
	
print_loop:
	lodsb
	or al, al
	jz print_end
	mov ah, 0x0E
	int 0x10
	jmp print_loop
	
print_end:
	leave
	ret

;---------------------------------------------
; Funcoes GDT
;---------------------------------------------

load_gdt:


	;xchg bx, bx
	
	push bp
	mov bp, sp
	
	; carregando gdt
	mov ax, 0x7c0
	mov ds, ax
	
	xchg bx, bx
	
	lgdt [gdt_ptr]
	
;	mov ax, 0x08
;	mov cs, ax
;	
;	mov ax, 0x10
;	mov ds, ax
;	mov es, ax
;	mov fs, ax
;	mov gs, ax
;	mov ss, ax
	
	leave
	ret
	
gdt_ptr:
	dw 24
	dd 0x7c00 + gdt
	
gdt:
	db 0, 0, 0, 0, 0, 0, 0, 0 			  ; null segment
	db 0xff, 0xff, 0, 0, 0, 0x9A, 0xCF, 0 ; code segment
	db 0xff, 0xff, 0, 0, 0, 0x92, 0xCF, 0 ; data segment

meuBootloader: db "Meu Bootloader", 13, 10, 0
carregandoKernel: db "Carregando kernel...", 13, 10, 0
	
times 510-($-$$) db 0 ; 2 bytes less now
db 0x55
db 0xAA
