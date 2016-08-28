
extern isr_handler
extern irq_handler

bits 32 	


%macro ISR_NOERRCODE 1 
global isr%1
isr%1:
      cli                  ; Disable interrupts.
      push 0		   ; Push a dummy error code.
      push %1		   ; Push the interrupt number
      jmp isr_common_stub  ;chamada
%endmacro


%macro ISR_ERRCODE 1 
global isr%1
isr%1:
      cli                  ; Disable interrupts.
      push %1		   ; Push the interrupt number
      jmp isr_common_stub  ;chamada
%endmacro
	

;------- MACROS GENÉRICAS PARA REQUEST HANDLER DAS INTERRUPÇÕES (IRQ) -------;

;parametro 1 é o numero da ISR e o parametro 2 é o mapeamento dele
%macro IRQ 2
global irq%1
irq%1:
      cli
      push 0
      push %2
      jmp irq_common_stub
%endmacro



ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31


IRQ   0,    32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47




global isr_common_stub
isr_common_stub:
	
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 

   mov ax, 0x08  	    
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call isr_handler	

   pop eax       
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa           
   add esp, 8     
   sti
   iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP



global irq_common_stub
irq_common_stub:
	
   pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

   mov ax, ds               ; Lower 16-bits of eax = ds.
   push eax                 

   mov ax, 0x08  	   
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call irq_handler

   pop eax     
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   popa           
   add esp, 8     
   sti
   iret       


