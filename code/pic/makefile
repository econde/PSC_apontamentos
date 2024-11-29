CFLAGS = -c -Wall -std=c2x -g --save-temps -Og

all: libpic.so main

main.o: main.c
	gcc $(CFLAGS) main.c -o main.o

libpic.o: libpic.c
	gcc $(CFLAGS) -fPIC libpic.c -o libpic.o

libpic.so: libpic.o
	gcc -shared -o libpic.so libpic.o

main: main.o
	gcc main.o -L. -lexa -o main

clean:
	rm -rf *.o *.i main
