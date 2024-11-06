#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

unsigned int get_time() {
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);
	return ts.tv_sec * 1000 + (ts.tv_nsec / 1000000);
}

typedef struct Word {
	char *text;
	int counter;
} Word;

/*------------------------------------------------------------------------------
 * Word
 */
char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";

char *word_read(FILE *fd){
	static char buffer[100];
	int i = 0, c;
	do {
		c = fgetc(fd);
		if (c == EOF) {
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

#include <glib.h>

GHashTable *htable;

gboolean word_equal(gconstpointer a, gconstpointer b) {
	return strcmp((char *)a, (char*)b) == 0;
}

guint hash_function(gconstpointer key) {
	const char *word_text = key;
	guint hash = 0;
	while (*word_text)
		hash += *word_text++;
	return hash;
}

void free_words(void *data) {
	free(((Word *)data)->text);
	free(data);
}

void text_free(gpointer key) {
}

void word_free(gpointer word) {
	free(((Word *)word)->text);
	free(word);
}

int main(int argc, char *argv[]){
	FILE *fd = fopen(argv[1], "r");
	if (NULL == fd) {
		fprintf(stderr, "fopen(%s, \"r\"): %s\n",
				argv[1], strerror(errno));
		exit(-1);
	}
	int nwords = 0;
	htable = g_hash_table_new_full(hash_function, word_equal, text_free, word_free);
	long initial = get_time();
	char *word_text = word_read(fd);
	while(word_text != NULL) {
		nwords++;
		Word *word = g_hash_table_lookup(htable, word_text);
		if (word != NULL) {
			word->counter++;
		}
		else {
			word = malloc(sizeof(Word));
			word->counter = 1;
			word->text = strdup(word_text);
			g_hash_table_insert(htable, word->text, word);
		}
		word_text = word_read(fd);
	}
	long duration = get_time() - initial;
	printf("Total de palavras = %d; "
			"Palavras diferentes = %d Time = %ld\n",
			nwords, g_hash_table_size(htable), duration);
//	printf("Collisions = %d\n", htable_collisions(htable));
	fclose(fd);
	g_hash_table_destroy(htable);
}

