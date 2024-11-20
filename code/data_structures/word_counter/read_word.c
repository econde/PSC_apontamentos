#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	BUFFER_WORD_CHUNK	30

static char *buffer_word_ptr;
static size_t word_max_size;

static void buffer_word_free(void) {
	free (buffer_word_ptr);
}

static int is_separator(const char *separators, char c) {
	return strchr(separators, c) != NULL;
}

char *read_word(FILE *file, const char *separators) {
	int index = 0;
	if (buffer_word_ptr == NULL) {
		buffer_word_ptr = malloc(BUFFER_WORD_CHUNK);
		if (buffer_word_ptr == NULL) {
			fprintf(stderr, "Out of memory\n");
			exit(EXIT_FAILURE);
		}
		word_max_size = BUFFER_WORD_CHUNK;
		atexit(buffer_word_free);
	}
	int c;
	do {
		c = fgetc(file);
		if (c == EOF)
			return NULL;
	} while (is_separator(separators, c));

	while ( !is_separator(separators, c) && c != EOF) {
		buffer_word_ptr[index++] = c;
		if (index == (word_max_size - 1)) { /* sempre uma posição disponível */
			char *aux = realloc(buffer_word_ptr, word_max_size + BUFFER_WORD_CHUNK);
			if (aux == NULL) {
				fprintf(stderr, "Out of memory\n");
				exit(EXIT_FAILURE);
			}
			word_max_size += BUFFER_WORD_CHUNK;
			buffer_word_ptr = aux;
		}
		c = fgetc(file);
	}
	if (index == 0 && c != '\n')
		return NULL;
	buffer_word_ptr[index] = '\0';
	return buffer_word_ptr;
}
