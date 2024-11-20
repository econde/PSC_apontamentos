#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#include "list.h"

char *read_word(FILE *file, char *separators);

unsigned int get_time();

char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";

typedef struct Word {
	char *text;
	int counter;
} Word;

struct list_node *words;

bool word_cmp(const void *data, const void *word_text) {
	return strcmp(((Word*)data)->text, (char *)word_text) == 0;
}

void free_word(void *data, void *) {
	free(((Word*)data)->text);
	free((void *)data);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		exit(-1);
	}
	FILE *fd = fopen(argv[1], "r");
	if (NULL == fd) {
		fprintf(stderr, "fopen(%s, \"r\"): %s\n",
				argv[1], strerror(errno));
		exit(-1);
	}
	int nwords = 0;
	words = list_create();

	long initial = get_time();
	char *word_text;
	while ((word_text = read_word(fd, separators)) != NULL) {
		nwords++;
		struct list_node *node = list_search(words, word_cmp, word_text);
		if (node != NULL) {
			Word *word = list_get_data(node);
			word->counter++;
		}
		else {
			Word *new_word = malloc(sizeof *new_word);
			if (new_word == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(EXIT_FAILURE);
			}
			/* new_word->text = word_text; ERRO */
			new_word->counter = 1;
			new_word->text = malloc(strlen(word_text) + 1);
			if (new_word->text == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(EXIT_FAILURE);
			}
//			printf("-%p\n", new_word->text); 
			strcpy(new_word->text, word_text);	// strdup
			list_insert_front(words, new_word);
		}
	}
	long duration = get_time() - initial;
	printf("Total de palavras = %d; "
	"Palavras diferentes = %ld Time = %ld\n",
		nwords, list_size(words), duration);
	fclose(fd);
	list_foreach(words, free_word, NULL);
	list_destroy(words);
}
