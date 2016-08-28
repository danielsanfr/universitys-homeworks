
extern kmain
global gdt_load

kernel:
	;xchg bx, bx
	call kmain
	;jmp kernel
	
gdt_load:
	
	xchg bx, bx	
	
	push ebp
	mov ebp, esp
	
	mov ax, 0x10
	mov ds, ax
	
	mov eax, [ebp+8]
	xchg bx, bx
	lgdt [eax]
	
	leave
	ret
	
