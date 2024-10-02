#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define  WORD_MAX_SIZE	30

#define  WORDS_MAX	40000

struct word {
	char word[WORD_MAX_SIZE];
	int counter;
};

struct word words[WORDS_MAX];
size_t words_counter;

void word_insert(char *word) {
	size_t i;
	for (i = 0; i < words_counter; ++i) {
		if (strcmp(words[i].word, word) == 0) {
			words[i].counter++;
			break;
		}
	}
	if (i == words_counter) {
		strcpy(words[words_counter++].word, word);
		words[i].counter = 1;
	}
}

void sort(struct word words[], size_t n) {
	for (size_t i = 0; i < n - 1; ++i)
		for (size_t j = 0; j < n - i - 1; ++j)
			if (words[j].counter < words[j + 1].counter) {
				struct word tmp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = tmp;
			}
}

void words_print(struct word words[], int n) {
	for (size_t i = 0; i < n; ++i)
		printf("%s - %d\n", words[i].word, words[i].counter);
}

char *separadores = " .,;!?\t\n\f:-\"\'\\/(){}[]*=%<>#";

int word_read(char buffer[], size_t buffer_size) {
	int i = 0, c;
	do {
		c = getchar();
		if (c == EOF){
			return EOF;
		}
	} while (strchr(separadores, c) != NULL);
	do {
		buffer[i++] = c;
		c = getchar();
		if (i == buffer_size - 1 || c == EOF)
			break;
	} while (strchr(separadores, c) == NULL);
	buffer[i] = '\0';
	return i;
}

int main() {
	char word_buffer[WORD_MAX_SIZE];

	while (word_read(word_buffer, sizeof word_buffer) != EOF)
		word_insert(word_buffer);

	sort(words, words_counter);

	words_print(words, 10);
}


