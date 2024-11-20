#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

char *read_word(FILE *file, char *separators);

unsigned int get_time();

struct word {
	char *text;
	int counter;
};

char *separators = " .,;!?\t\n\f:-\"\'(){}[]*=%><#+-&";

static inline int min(int a, int b) {
	return a < b ? a : b;
}

#include "htable.h"

struct htable *htable;

int word_cmp_text(const void *data, const void *b) {
	return strcmp(((struct word *)data)->text, (char*)b);
}

int hash_function(const void *data) {
	const char *word_text = data;
	int hash = 0;
	while (*word_text)
		hash += *word_text++;
	return hash;
}

void free_words(void *data, void *context) {
	free(((struct word *)data)->text);
	free(data);
}

//------------------------------------------------------------------------------

#include "slist.h"

int cmp_counter(const void *data, const void *context) {
	struct word *ref = (struct word *)data;
	struct word *new = (struct word *)context;
	if (ref->counter > new->counter)
		return +1;
	else if (ref->counter < new->counter)
		return -1;
	return 0;
}

//------------------------------------------------------------------------------

typedef struct Top_ten {
	struct slist_node *list;
	int lower_counter;
	int list_size;
} Top_ten;

static void insert_in_list(void *data, void *context) {
	Top_ten *stuff = (Top_ten*)context;
	struct word *word = (struct word *)data;
	if (stuff->list_size < 10) {
		stuff->list = slist_insert_sort(stuff->list, cmp_counter, data);
		stuff->list_size++;
		stuff->lower_counter = ((struct word *)slist_data(stuff->list))->counter;
	}
	else if (word->counter > stuff->lower_counter) {
		stuff->list = slist_insert_sort(stuff->list, cmp_counter, data);
		stuff->list = slist_remove_head(stuff->list);
		stuff->lower_counter = ((struct word *)slist_data(stuff->list))->counter;
	}
}

static struct slist_node *get_top_ten(struct htable *htable) {
	Top_ten stuff = { NULL, 0, 0 };
	htable_foreach(htable, insert_in_list, &stuff);
	return stuff.list;
}

static void print_word(void *a, void *) {
	struct word *word = a;
	printf("%s - %d\n", word->text, word->counter);
}

int main(int argc, char *argv[]){
	FILE *fd = fopen(argv[1], "r");
	if (NULL == fd) {
		fprintf(stderr, "fopen(%s, \"r\"): %s\n",
				argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	int nwords = 0;
	htable = htable_create(10000, hash_function, word_cmp_text);
	long initial = get_time();
	char *word_text;
	while((word_text = read_word(fd, separators)) != NULL) {
		nwords++;
		struct word *word = htable_lookup(htable, word_text);
		if (word != NULL) {
			word->counter++;
		}
		else {
			word = malloc(sizeof(struct word));
			word->counter = 1;
			word->text = strdup(word_text);
			htable_insert(htable, word_text, word);
		}
	}
	long duration = get_time() - initial;
	printf("Total de palavras = %d; "
			"Palavras diferentes = %ld Time = %ld\n",
			nwords, htable_size(htable), duration);
	printf("Collisions = %d\n", htable_collisions(htable));

	struct slist_node *top_ten_list = get_top_ten(htable);
	slist_foreach(top_ten_list, print_word, NULL);
	slist_destroy(top_ten_list);

	fclose(fd);
	htable_foreach(htable, free_words, NULL);
	htable_destroy(htable);
}
