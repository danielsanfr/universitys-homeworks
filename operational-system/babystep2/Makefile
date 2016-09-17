# Assembly compiler
AC=nasm
# Convert and copy a file
DD=dd

all: bootloader.bin

bootloader.bin: bootloader.asm
	$(AC) bootloader.asm -f bin -o bootloader.bin
	
print.o: print.asm
	$(AC) print.asm -f bin -o print.o

install:
	sudo $(DD) if=bootloader.bin of=/dev/fd0

clean:
	rm -f bootloader.o bootloader.bin
