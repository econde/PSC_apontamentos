#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

static inline int min(int a, int b) {
	return a < b ? a : b;
}

char *word_read(FILE *file, char *separators);

char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";

unsigned int get_time() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

/*------------------------------------------------------------------------------
 * Word
 */
struct word {
	char *text;
	int counter;
};

#include "tree.h"

int word_cmp_text(const void *a, const void *b) {
	const struct word *one_word = a;
	const struct word *another_word = b;
	return strcmp(one_word->text, another_word->text);
}

void free_words(void *data) {
	free(((struct word *)data)->text);
	free(data);
}

int main(int argc, char *argv[]) {
	FILE *fd = fopen(argv[1], "r");
	if (NULL == fd) {
		fprintf(stderr, "fopen(%s, \"r\"): %s\n",
				argv[1], strerror(errno));
		return EXIT_FAILURE;
	}
	int nwords = 0;
	struct tree_node *words = NULL;
	unsigned initial_timepoint = get_time();
	char *word_text;
	while ((word_text = wordread(fd, separators)) != NULL) {
		nwords++;
		struct word key = {.text = word_text};
		struct tree_node *node = tree_search(words, &key, word_cmp_text);
		if (node != NULL) {
			struct word *word = tree_data(node);
			word->counter++;
		}
		else {
			struct word *word = malloc(sizeof(Word));
			if (word == NULL) {
				fprintf(stderr, "Out of memory\n");
				return EXIT_FAILURE;
			}
			word->counter = 1;
			word->text = strdup(word_text);
			if (word->text == NULL) {
				fprintf(stderr, "Out of memory\n");
				return EXIT_FAILURE;
			}
			words = tree_insert(words, word, word_cmp_text);
		}
	}
	unsigned duration = get_time() - initial_timepoint;
	printf("Total de palavras = %d; "
			"Palavras diferentes = %ld; Time = %ld ms\n",
		nwords, tree_size(words), duration);
	printf("Profundidade da árvore = %d\n", tree_depth(words));
	/* libertar os recursos alocados */
	fclose(fd);
	tree_foreach(words, free_words);
	tree_destroy(words);
}
