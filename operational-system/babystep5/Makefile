# Assembly compiler
AC=nasm
# C compiler
CC=gcc
# Convert and copy a file
DD=dd
# Linker
LD=ld

all: init bootloader.bin kernel.bin
	cat dist/bootloader.bin dist/kernel.bin > dist/floppy.bin
	sudo dd if=dist/floppy.bin of=/dev/fd0
	
init: 
	mkdir -p dist

kernel.bin: src/kernel/hang.c src/kernel/kernel.c
	$(CC) -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/hang.o src/kernel/hang.c
	$(CC) -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -o dist/kernel.o src/kernel/kernel.c
	$(LD) -T link.ld dist/kernel.o dist/hang.o -o dist/kernel.bin
	
bootloader.bin: src/bootloader/bootloader.asm
	$(AC) src/bootloader/bootloader.asm -f bin -o dist/bootloader.bin

install:
	sudo $(DD) if=dist/floppy.bin of=/dev/fd0

clean:
	rm -Rf dist

