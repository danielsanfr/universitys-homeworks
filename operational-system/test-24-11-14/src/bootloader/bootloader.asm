bits 16      ;16-bit Real Mode
org 0x7c00   ;esse bootloader inicia nesse endereço de memória 

global start
start:
	push bp   ;stack reference
	mov bp, sp

	;xchg bx, bx ;no debugg do bochs, ir na Physical Mem Dump : 0x08200 (inicialmente vazia)
	
	call load_kernel
	
	cli ;reseta a flag de interrupções para zero
	
	;xchg bx, bx ;ir no debugg do bochs, Mem Dump : 0x08200 (kernel estará carregado lá)
	
	call gdt_bootloader_load ;carregando a tabela "gdt" definida no bootloader
	
	;xchg bx, bx  ;ir no debugg do bochs, View > GDT (teremos nossos três segmentos)

	call switch_protected_mode ;entrar no modo protegido

	;sti ;habilitando interrupções

	;xchg bx, bx  ;ir no debugg do bochs, na barra de status mostrará: Protected Mode
	
	jmp 0x08:0x8200	    ;chamado de "far jump" é definido por: <segment>:<address_offset>
	;pula para o segmento de código

;vai carregar o kernel no endereço passado no parametro (0x8200)
global load_kernel
load_kernel:
	push bp  	;stack reference 
	mov bp, sp

	mov ah, 0x02 ;INT 13h / AH = 02h - read disk sectors into memory.
	
	mov al, 0x0F ;quantidade de setores a serem lidos ou escritos (não pode ser zero 0)
	
	mov ch, 0x00 ;número do cilindro (0..79). (floppy só tem um cilindro)
	mov cl, 0x02 ;número do setor (1..18)
	mov dh, 0x00 ;número da face (0..1) (face de cima)
	mov dl, 0x00 ;número do drive (0..3, depende da quantidade de FLOPPYS) (primeiro floppy)

	mov bx, 0x820 ;
	
	mov es, bx    ;ES:BX - 512 bytes após o bootloader
	mov bx, 0x00

	int 0x13
	leave
	ret


;vai carregar a GDT definida abaixo (gdt do bootloader)
global gdt_bootloader_load
gdt_bootloader_load:

	push bp
	mov bp, sp
		
	lgdt [gdt_bootloader_ptr] ;carrega a gdt a partir do ponteiro da gdt
	
	leave
	ret


;trocar para o modo protegido - inabilitando a abertura de várias funções da BIOS
global switch_protected_mode	
switch_protected_mode:
	
	push bp
	mov bp, sp
	
	; habilitar o modo protegido.
	
	mov eax, cr0    ;set do primeiro bit de cr0 para ativar a PM
	or eax, 1
	mov cr0, eax

	;os valores atualizados nos registradores de segmentos
	mov ax, 0x10      
	mov ds, ax	 ; 0x10 é o offset na GDT para data segment
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	leave
	ret

;ponteiro da GDT a ser carregada no bootloader
gdt_bootloader_ptr:
	dw 24
	dd gdt_bootloader
	
;definição dos segmentos da GDT
gdt_bootloader: ;endereço para a gdt
	db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 ; segmento nulo
	db 0xff, 0xff, 0x00, 0x00, 0x00, 0x9A, 0xCF, 0x00 ; segmento de código
	db 0xff, 0xff, 0x00, 0x00, 0x00, 0x92, 0xCF, 0x00 ; segmento de dados

     ;a instrução times será utilizada para determinar o tamanho de todo o código e os dados reunidos.
     times 510-($-$$) db 0x00 	;Quando compilado, nosso programa deverá conter 512 bytes
     db 0x55
     db 0xAA	;assinatura do bootloader (para a BIOS saber que é um bootloader).

