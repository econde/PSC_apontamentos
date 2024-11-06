#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include "vector_ptr.h"

unsigned int get_time() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

typedef struct Word {
	char *text;
	int counter;
} Word;

char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";

char *word_read(FILE *fd){
	static char buffer[100];
	int i = 0, c;
	do {
		c = fgetc(fd);
		if(c == EOF){
			return NULL;
		}
	}
	while (strchr(separators, c) != NULL);
	do {
		buffer[i++] = c;
		c = fgetc(fd);
		if(c == EOF)
			break;
	} while (strchr(separators, c) == NULL);
	buffer[i] = '\0';
	return buffer;
}

static inline int min(int a, int b) {
	return a < b ? a : b;
}

PVector *words;

int word_cmp_text(const void *a, const void *b) {
	return strcmp((*(Word **)a)->text, (const char *)b);
}

int word_cmp_count(const void *a, const void *b) {
	return (*(Word **)a)->counter - (*(Word **)b)->counter;
}

int word_cmp_count_decrease(const void *a, const void *b) {
	return (*(Word **)b)->counter - (*(Word **)a)->counter;
}

void free_words(void *data) {
	free(((Word *)data)->text);
	free(data);
}

int main(int argc, char *argv[]){
	FILE *fd = fopen(argv[1], "r");
	if (NULL == fd) {
		fprintf(stderr, "fopen(%s, \"r\"): %s\n",
				argv[1], strerror(errno));
		exit(-1);
	}
	int nwords = 0;
	words = pvector_create(1000);
	long initial = get_time();
	char *word_text = word_read(fd);
	while (word_text != NULL) {
		nwords++;
		size_t index;
		if (pvector_sorted_search(words, word_text,
								word_cmp_text, &index)) {
			Word *w = pvector_at(words, index);
			w->counter++;
		}
		else {
			Word *w = malloc(sizeof(Word));
			w->counter = 1;
			w->text = strdup(word_text);
			pvector_insert(words, w, index);
		}
		word_text = word_read(fd);
	}
	long duration = get_time() - initial;
	fclose(fd);
	printf("Total de palavras = %d; "
		   "Palavras diferentes = %ld Time = %ld\n",
		    nwords, pvector_size(words), duration);
	pvector_sort(words, word_cmp_count_decrease);
	for(size_t i = 0; i < min(10, pvector_size(words)); ++i) {
//	for(size_t i = 0; i < pvector_size(words); ++i) {
		Word *w = pvector_at(words, i);
		printf("%s - %d\n", w->text, w->counter);
	}
	pvector_foreach(words, free_words);
	pvector_destroy(words);
}

