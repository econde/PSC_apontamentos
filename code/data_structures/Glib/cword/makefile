
CFLAGS = -c -g -Werror -Wall -pedantic `pkg-config gtk+-3.0 --cflags`

LFLAGS= `pkg-config gtk+-3.0 --libs`

all: cword_vector_ptr cword_vector cword_tree cword_htable cword_list

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

cword_htable: cword_htable.o
	gcc cword_htable.o $(LFLAGS) -o cword_htable

cword_tree: cword_tree.o
	gcc cword_tree.o $(LFLAGS) -o cword_tree

cword_vector: cword_vector.o
	gcc cword_vector.o $(LFLAGS) -o cword_vector

cword_vector_ptr: cword_vector_ptr.o
	gcc cword_vector_ptr.o $(LFLAGS) -o cword_vector_ptr

cword_list: cword_list.o
	gcc cword_list.o $(LFLAGS) -o cword_list

clean:
	rm -rf *.o cword_list cword_tree cword_vector cword_vector_ptr cword_htable
