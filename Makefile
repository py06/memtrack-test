CFLAGS=-lm

test.o:
	gcc $(CFLAGS) -o test test.c

test:	test.o
