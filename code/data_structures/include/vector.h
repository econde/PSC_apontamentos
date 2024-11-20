#ifndef VECTOR_H
#define VECTOR_H

struct vector;

struct vector *vector_create(size_t element_size, size_t chunk_size);

void vector_destroy(struct vector *);

bool vector_insert(struct vector *vector, void *element, size_t index);
void vector_remove(struct vector *vector, size_t index);

void *vector_at(struct vector *vector, int index);

void *vector_assign(struct vector *vector, int index, void *element);

size_t vector_size(struct vector *vector);

bool vector_search(struct vector *vector, void *key,
					int (*compare)(const void *, const void *), size_t *);

void vector_sort(struct vector *vector, int (*cmp)( const void *, const void *));
bool vector_sorted_search(struct vector *vector, void *key,
							int (*compare)(const void *, const void *), size_t *index);

void vector_foreach(struct vector *vector, void(*do_it)(void *, void*), void *context);

#if 0
int vector_sort_insert(struct vector *vector, void *element,
						int (*cmp)( const void *, const void *));

int vector_sort_remove(struct vector *vector, void *element,
					int (*cmp)(const void *, const void *));
#endif

#endif
