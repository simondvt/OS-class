CFLAGS = -Wall

target: process.o
	gcc $(CFLAGS) process.o -o process

process.o: process.c
	gcc $(CFLAGS) -c process.c 

clean:
	rm process.o
