
global gdt_load
gdt_load:
    
    push ebp
    mov ebp, esp

   

    mov eax, [ebp+8]  
    
    ;xchg bx, bx
    
    lgdt [eax]       
    mov ax, 0x08      
    mov ds, ax		
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ;xchg bx, bx

    jmp 0x10:complete_flush     
   		      		
complete_flush:
   
    leave
    ret              

