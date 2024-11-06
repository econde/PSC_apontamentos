#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

char *readword(FILE *file, const char *separators);
unsigned int get_time();

#define	ARRAY_SIZE(a)	(sizeof a / sizeof a[0])

char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";


struct word {
	char *text;
	int counter;
};

#define  WORDS_MAX	30000

static struct word words[WORDS_MAX];
static int words_counter;

bool words_search(const char *word, int *index) {
//	for (int i = 0; i < words_counter; ++i)
	for (int i = words_counter - 1; i >= 0; --i)
		if (strcmp(words[i].text, word) == 0) {
			*index = i;
			return true;
		}
	return false;
}

void words_insert(const char *word) {
	words[words_counter].counter = 1;
	words[words_counter].text = malloc(strlen(word) + 1);
	if (words[words_counter].text == NULL) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
	strcpy(words[words_counter].text, word);
	words_counter++;
}

void swap(struct word *a, struct word *b) {
	struct word aux = *a;
	*a = *b;
	*b = aux;
}

void words_sort(struct word array[], size_t array_length) {
	for (size_t i = 0; i < array_length - 1; i++)
		for (size_t j = 0; j < array_length - 1 - i; j++)
			if (array[j].counter < array[j + 1].counter)
				swap(&array[j], &array[j + 1]);
}

void words_print(struct word array[], size_t array_length) {
	for (size_t i = 0; i < array_length; i++)
		printf("%s - %d\n", words[i].text, array[i].counter);
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	FILE *fd = fopen(argv[1], "r");
	if (fd == NULL) {
		fprintf(stderr, "fopen(%s): %s\n", argv[1], strerror(errno));
		return EXIT_FAILURE;
	}
	unsigned initial = get_time();
	char *word;
	int nwords = 0;
	while ((word = readword(fd, separators)) != NULL) {
		nwords++;
		int i;
		if (words_search(word, &i))
			words[i].counter++;
		else if (words_counter < ARRAY_SIZE(words))
			words_insert(word);
		else
			printf("Word array is full\n");
	}
	unsigned elapsed = get_time() - initial;
	printf("Total de palavras = %d; "
	       "Palavras diferentes = %d Time = %d\n",
	       nwords, words_counter, elapsed);
	words_sort(words, words_counter);
	words_print(words, 10);
	fclose(fd);
}
















