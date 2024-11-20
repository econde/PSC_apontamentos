#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "vector.h"

char *read_word(FILE *file, char *separators);

unsigned int get_time();

static char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";

static inline int min(int a, int b) {
	return a < b ? a : b;
}

struct word {
	char *text;
	int counter;
};

struct vector *words;

int word_cmp_text(const void *a, const void *b) {
	return strcmp((const char *)a, ((struct word *)b)->text);
}

int word_cmp_count(const void *a, const void *b) {
	return ((struct word *)a)->counter - ((struct word *)b)->counter;
}

int word_cmp_count_decrease(const void *a, const void *b) {
	return ((struct word *)b)->counter - ((struct word *)a)->counter;
}

void free_word(void *data, void *) {
	free(((struct word *)data)->text);
}

void print_top_ten(struct vector *words, size_t size) {;
	for (size_t i = 0; i < size; ++i) {
		struct word *w = vector_at(words, i);
		printf("%s - %d\n", w->text, w->counter);
	}
}

int main(int argc, char *argv[]){
	FILE *fd = fopen(argv[1], "r");
	if (NULL == fd) {
		fprintf(stderr, "fopen(%s, \"r\"): %s\n", argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	int nwords = 0;
	words = vector_create(sizeof (struct word), 2);
	long initial = get_time();
	char *word_text;
	while ((word_text = read_word(fd, separators)) != NULL) {
		nwords++;
		size_t index;
		if (vector_sorted_search(words, word_text, word_cmp_text, &index)) {
			struct word *w = vector_at(words, index);
			w->counter++;
		}
		else {
			struct word w = { .counter = 1 };
			w.text = strdup(word_text);
			if (w.text == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(EXIT_FAILURE);
			}
			vector_insert(words, &w, index);
		}
	}
	long duration = get_time() - initial;
	fclose(fd);
	printf("Total de palavras = %d; Palavras diferentes = %zd Time = %ld\n",
			nwords, vector_size(words), duration);
	vector_sort(words, word_cmp_count_decrease);
	print_top_ten(words, min(10, vector_size(words)));
	vector_foreach(words, free_word, NULL);
	vector_destroy(words);
}
