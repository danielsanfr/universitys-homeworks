
global enable_paging
global update_directory


enable_paging:
	push ebp
	mov ebp, esp
	
	xchg bx, bx
	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax
	
	leave
	ret
	
update_directory:
	push ebp
	mov ebp, esp
	
	
	xchg bx, bx
	mov eax, [ebp+8]
	
	mov cr3, eax
	
	leave
	ret
