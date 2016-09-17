# Assembly compiler
AC=nasm
# C compiler
CC=gcc
# Convert and copy a file
DD=dd
# Linker
LD=ld
CFLAGS=-Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions \
 -nostdinc -fno-builtin -c -o

all: init bootloader.bin kernel.bin 
	cat dist/bootloader.bin dist/kernel.bin > dist/floppy.bin
	
init: 
	mkdir -p dist

kernel.bin: src/kernel/kernel.asm src/kernel/kernel.c
	$(AC) src/kernel/kernel.asm -f elf32 -o dist/kernel1.o
	$(CC) $(CFLAGS) dist/kernel2.o src/kernel/kernel.c
	$(LD) -T link.ld dist/kernel1.o dist/kernel2.o -o dist/kernel.bin
	
bootloader.bin: src/bootloader/bootloader.asm
	$(AC) src/bootloader/bootloader.asm -f bin -o dist/bootloader.bin

install:
	sudo $(DD) if=dist/floppy.bin of=/dev/fd0
	
clean:
	rm -Rf dist

