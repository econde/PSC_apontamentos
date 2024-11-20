/*	Instituto Superior de Engenharia de Lisboa
	Ezequiel Conde, 2022
*/
#include "htable.h"

struct htable {
	struct slist_node **base;
	size_t size;
	int (*hash_function)(const void *);
	int (*key_function)(const void *, const void *);
};

void htable_init(struct htable *htable, size_t size,
				int (*hf)(const void *),
				int (*kf)(const void *, const void *)) {
	htable->hash_function = hf;
	htable->key_function = kf;
	htable->size = size;
	for (size_t i = 0; i < size; ++i)
		htable->base[i] = NULL;
}

struct htable *htable_create(size_t size,
				int (*hf)(const void *),
				int (*kf)(const void *, const void *)) {
	struct htable *htable = malloc(sizeof(struct htable));
	if (NULL == htable)
		return NULL;
	htable->base = malloc(sizeof *htable->base * size);
	if (NULL == htable->base){
		free(htable);
		return NULL;
	}
	htable_init(htable, size, hf, kf);
	return htable;
}

void htable_destroy(struct htable *htable) {
	for (size_t i = 0; i < htable->size; ++i)
		if (htable->base[i] != NULL)
			slist_destroy(htable->base[i]);
	free(htable->base);
	free(htable);
}

int htable_insert(struct htable *htable, const void *key, void *data) {
	int index = htable->hash_function(key) % htable->size;
	htable->base[index] = slist_insert(htable->base[index], data);
	return htable->base[index] != NULL;
}

void htable_remove(struct htable *htable, const void *key) {
	int index = htable->hash_function(key) % htable->size;
	if (NULL == htable->base[index])
		return;
	struct slist_node *node = slist_search(htable->base[index],
								key, htable->key_function);
	if (NULL != node)
		htable->base[index] = slist_remove(htable->base[index], node);
}

void *htable_lookup(struct htable *htable, const void *key) {
	int index = htable->hash_function(key) % htable->size;
	if (NULL == htable->base[index])
		return NULL;
	struct slist_node *node = slist_search(htable->base[index],
									key, htable->key_function);
	if (node != NULL)
		return slist_data(node);
	return NULL;
}

void htable_foreach(struct htable *htable, void (*do_it)(void*, void *), void *context) {
	for (size_t i = 0; i < htable->size; ++i)
		if (htable->base[i] != NULL)
			slist_foreach(htable->base[i], do_it, context);
}

size_t htable_size(struct htable *htable) {
	int i, counter = 0;
	for (i = 0; i < htable->size; ++i)
		if (NULL != htable->base[i])
			counter += slist_size(htable->base[i]);
	return counter;
}

int htable_collisions(struct htable * htable) {
	int i, max_collisions = 0;
	for (i = 0; i < htable->size; ++i) {
		if (NULL != htable->base[i]) {
			int collisions = slist_size(htable->base[i]);
			if (collisions > max_collisions)
				max_collisions = collisions;
		}
	}
	return max_collisions - 1;
}
