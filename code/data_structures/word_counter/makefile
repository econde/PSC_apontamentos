
CFLAGS = -c -g -Werror -Wall -I../include -std=c2x

LFLAGS=

VPATH = ../lib

all: wcounter_array wcounter_vector_ptr wcounter_vector wcounter_tree wcounter_htable wcounter_list

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

wcounter_htable: wcounter_htable.o htable.o slist.o readword.o
	gcc	$(LFLAGS) wcounter_htable.o htable.o slist.o readword.o -o wcounter_htable

wcounter_tree: wcounter_tree.o tree.o readword.o
	gcc	$(LFLAGS) wcounter_tree.o tree.o readword.o -o wcounter_tree

wcounter_vector: wcounter_vector.o vector.o readword.o get_time.o
	gcc	$(LFLAGS) wcounter_vector.o vector.o readword.o get_time.o -o wcounter_vector

wcounter_vector_ptr: wcounter_vector_ptr.o vector_ptr.o readword.o
	gcc	$(LFLAGS) wcounter_vector_ptr.o vector_ptr.o readword.o -o wcounter_vector_ptr

wcounter_list: wcounter_list.o list.o readword.o
	gcc	$(LFLAGS) wcounter_list.o list.o readword.o -o wcounter_list

wcounter_array: wcounter_array.o readword.o get_time.o
	gcc	$(LFLAGS) wcounter_array.o readword.o get_time.o -o wcounter_array

clean:
	rm -rf *.o wcounter_array wcounter_list wcounter_tree wcounter_vector wcounter_vector_ptr wcounter_htable
