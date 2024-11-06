
CFLAGS = -c -g -Werror -Wall -pedantic -std=c2x -I../include

LFLAGS=

VPATH = ../lib

all: wqueue1 wqueue2 wqueue3 wqueue4 wqueue5 wqueue6

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

wqueue1: wqueue1.o
	gcc $(LFLAGS) wqueue1.o -o wqueue1

wqueue2: wqueue2.o
	gcc $(LFLAGS) wqueue2.o -o wqueue2

wqueue3: wqueue3.o
	gcc $(LFLAGS) wqueue3.o -o wqueue3

wqueue4: wqueue4.o list.o
	gcc $(LFLAGS) wqueue4.o list.o -o wqueue4

list.o: ../src/list.c ../include/list.h
	gcc $(CFLAGS) ../src/list.c -o list.o

wqueue5: wqueue5.o ilist.o
	gcc $(LFLAGS) wqueue5.o ilist.o -o wqueue5

ilist.o: ../src/ilist.c ../include/ilist.h
	gcc $(CFLAGS) ../src/ilist.c -o ilist.o

wqueue6.o: wqueue6.c
	gcc -o $*.o $(CFLAGS) `pkg-config glib-2.0 --cflags` $<

wqueue6: wqueue6.o
	gcc $(LFLAGS) wqueue6.o `pkg-config glib-2.0 --libs` -o wqueue6

clean:
	rm -rf *.o wqueue1 wqueue2 wqueue3 wqueue4 wqueue5 wqueue6 a.out
