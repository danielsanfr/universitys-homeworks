#Interação Paginação
all: initv4 bootloaderv4 kernelv4 monitorv4 utilsv4 gdtv4 gdt_loadv4 idtv4 idt_loadv4 isrv4 isr_loadv4 timerv4 keyboardv4 pagingv4 loadpagingv4 linking_objectsv4
	
	cat dist/boot.bin dist/kernel.bin > dist/floppy.bin
	#cat dist/boot.bin > dist/floppy.bin
	#juntando os dois binários, concatenando os arquivos (2 setores: Bootloader e Kernel)
	
	sudo dd if=dist/floppy.bin of=/dev/fd0
	
initv4: 
	mkdir -p dist

kernelv4:	
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/kernel.o src/kernel/kernel.c
	#gerado .o do kernel

monitorv4:
	#adicionado a flag "-fno-stack-protector" para evitar o erro de "undefined reference to `__stack_chk_fail'" para a compilacao das funcoes do monitor
	gcc -Wall -O -fno-stack-protector -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/monitor.o src/kernel/monitor.c
	#gerado .o do monitor (escrita na tela)

utilsv4:
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/utils.o src/kernel/utils.c
	#gerado .o de utils (funções úteis para uso de strings e escrita de bytes na tela)

gdtv4:
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/gdt.o src/kernel/gdt.c
	#gerado .o da gdt
gdt_loadv4:
	nasm -f elf src/kernel/gdt_load.asm -o dist/gdt_load.o
	#gerado .o da gdt_load

idtv4:
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/idt.o src/kernel/idt.c
	#gerado .o da idt
idt_loadv4:
	nasm -f elf src/kernel/idt_load.asm -o dist/idt_load.o
	#gerado .o da idt_load

isrv4:
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/isr.o src/kernel/isr.c
	#gerado .o da isr
isr_loadv4:
	nasm -f elf src/kernel/isr_load.asm -o dist/isr_load.o
	#gerado .o da isr_load

timerv4:
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/timer.o src/kernel/timer.c
	#gerado .o do tick (timer)

keyboardv4:
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/keyboard.o src/kernel/keyboard.c
	#gerado .o do teclado (leitura buffer por interrupção)

pagingv4:
	gcc -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/paging.o src/kernel/paging.c
	#gerado .o da paging

loadpagingv4:
	nasm src/kernel/paging.asm -f elf32 -o dist/loadpaging.o
	#gerado .o da paging


linking_objectsv4:	
	ld -T link.ld dist/kernel.o dist/monitor.o dist/utils.o dist/gdt_load.o dist/gdt.o dist/idt_load.o dist/idt.o dist/isr_load.o dist/isr.o dist/timer.o dist/keyboard.o dist/paging.o dist/loadpaging.o -o dist/kernel.bin
	#linkando os .o's do monitor, das funções úteis (util), da gdt, da idt, da isr (interrupções e tratamentos), e do kernel. Gerando o binário kernel.

bootloaderv4:
	nasm src/bootloader/bootloader.asm -f bin -o dist/boot.bin
	#gerado o binário do bootloader

clean:
	rm -Rf dist
	clear

