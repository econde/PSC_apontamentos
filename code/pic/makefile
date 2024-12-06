CFLAGS = -c -Wall -std=c2x -g -Og

all: main

main.o: main.c
	gcc $(CFLAGS) main.c -o main.o

main: main.o
	gcc main.o -L. -lpic -o main

clean:
	rm -rf *.o *.i main
