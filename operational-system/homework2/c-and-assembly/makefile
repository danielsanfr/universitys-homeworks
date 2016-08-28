# C compiler
CC=gcc

all: main.o prime.o
	$(CC) -o prime.out main.o prime.o

main.o: main.c
	$(CC) -c main.c -o main.o

prime.o: prime.s
	$(CC) -c prime.s -o prime.o

clean:
	rm -f *.o*
