/*	Instituto Superior de Engenharia de Lisboa
	Ezequiel Conde, 2010

	As listas de colisão têm sentinela na própria tabela
*/
#ifndef HTABLE_H
#define HTABLE_H

#include <stdlib.h>
#include "slist.h"

struct htable;

#define STATIC_HTABLE(name, size, hash_function) \
	static struct slist_node *name##links[size]; \
	static struct htable name = { name##links, size, hash_function }


void htable_init(struct htable *, size_t,
				int (*hash_function)(const void *),
				int (*key_function)(const void *, const void *));

struct htable *htable_create(size_t,
				int (*hash_function)(const void *),
				int (*key_function)(const void *, const void *));

void htable_destroy(struct htable *);

int htable_insert(struct htable *table, const void *key, void *data);

void htable_remove(struct htable *htable, const void *key);

void *htable_lookup(struct htable *htable, const void *key);

void htable_foreach(struct htable *, void (*do_it)(void*, void*), void *context);

size_t htable_size(struct htable *table);

int htable_collisions(struct htable *table);

#endif
