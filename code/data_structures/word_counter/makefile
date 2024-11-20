
CFLAGS = -c -g -Werror -Wall -I../include -std=c2x

LFLAGS=

VPATH = ../src

all: wcounter_array wcounter_vector_ptr wcounter_vector wcounter_tree wcounter_htable wcounter_list

%.o: %.c
	gcc -o $*.o $(CFLAGS) $<

wcounter_htable: wcounter_htable.o htable.o slist.o read_word.o get_time.o
	gcc	$(LFLAGS) wcounter_htable.o htable.o slist.o read_word.o get_time.o -o wcounter_htable

wcounter_tree: wcounter_tree.o tree.o read_word.o get_time.o
	gcc	$(LFLAGS) wcounter_tree.o tree.o read_word.o get_time.o -o wcounter_tree

wcounter_vector: wcounter_vector.o vector.o read_word.o get_time.o
	gcc	$(LFLAGS) wcounter_vector.o vector.o read_word.o get_time.o -o wcounter_vector

wcounter_vector_ptr: wcounter_vector_ptr.o vector_ptr.o read_word.o get_time.o
	gcc	$(LFLAGS) wcounter_vector_ptr.o vector_ptr.o read_word.o get_time.o -o wcounter_vector_ptr

wcounter_list: wcounter_list.o list.o read_word.o get_time.o
	gcc	$(LFLAGS) wcounter_list.o list.o read_word.o get_time.o -o wcounter_list

wcounter_array: wcounter_array.o read_word.o get_time.o
	gcc	$(LFLAGS) wcounter_array.o read_word.o get_time.o -o wcounter_array

clean:
	rm -rf *.o wcounter_array wcounter_list wcounter_tree wcounter_vector wcounter_vector_ptr wcounter_htable
