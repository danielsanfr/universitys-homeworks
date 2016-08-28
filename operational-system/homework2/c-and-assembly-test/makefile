# C compiler
CC=gcc
# Assembly compiler
AC=nasm

all: main.o add.o
	$(CC) -o add.out main.o add.o

main.o: main.c
	$(CC) -c main.c -o main.o

add.o: add.s
	$(AC) -f elf -o add.o add.s

clean:
	rm -f *.o*
