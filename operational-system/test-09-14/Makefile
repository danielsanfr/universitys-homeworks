# Assembly compiler
AC=nasm
# Convert and copy a file
DD=dd

all: bootloader.bin

bootloader.bin: bootloader.asm clear.asm set_pos.asm print.asm kernel.asm
	$(AC) bootloader.asm -f bin -o bootloader.bin
	$(AC) kernel.asm -f bin -o kernel.bin
	
print.o: print.asm
	$(AC) print.asm -f bin -o print.o

install: bootloader.bin kernel.bin
	cat bootloader.bin kernel.bin > floppy.bin
	sudo $(DD) if=floppy.bin of=/dev/fd0
	rm -f floppy.bin

clean:
	rm -f bootloader.o bootloader.bin kernel.o kernel.bin floppy.bin
