#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

struct vector *vector_create(size_t element_size, size_t chunk_size) {
	struct vector *vector = malloc(sizeof *vector);
	if (NULL == vector)
		return NULL;
	vector->buffer = malloc(element_size * chunk_size);
	if (NULL == vector->buffer) {
		free(vector);
		return NULL;
	}
	vector->element_size = element_size;
	vector->chunk_size = chunk_size;
	vector->max_size = chunk_size;
	vector->current_size = 0;
	return vector;
}

void vector_destroy(struct vector *vector) {
	free(vector->buffer);
	free(vector);
}

/*	Pesquisa dicotómica sobre o vetor ordenado
 *	retorna um valor booleano indicando se encontrou
 *	devolve através de index a posição onde encontrou ou deveria encontrar
 */
bool vector_sorted_search(struct vector *vector, void *key,
	                      int (*compare)(const void *, const void *), size_t *index) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	size_t ref = 0;
	char *buffer = vector->buffer;
	while (left < right) {
		int compare_result = compare(key, buffer + middle * vector->element_size);
		if (compare_result > 0) {
			ref = left = middle + 1;
		}
		else if (compare_result < 0) {
			ref = right = middle;
		}
		else {
			*index = middle;
			return true;
		}
		middle = left + (right - left) / 2;
	}
	*index = ref;
	return false;
}

#if 0

/*	Insere um novo elemento num vetor ordenado.
	A inserção implica o avanço dos elementos seguintes,
	com eventual aumento da memória alocada.
	Retorna verdadeiro se a inserção de realizar ou o se elemento já existir.
*/
bool vector_sorted_insert(struct vector *vector, void *element,
					int (*compare)( const void *, const void *)) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	size_t ref = 0;
	char *buffer = vector->buffer;
	while (left < right) {
		int compare_result = compare(element, buffer + middle * vector->element_size);
		if (compare_result > 0)
			ref = left = middle + 1;
		else if (compare_result < 0)
			ref = right = middle;
		else
			return true;
		middle = left + (right - left) / 2;
	}
	if (vector->current_size == vector->max_size) {
		vector->buffer = buffer = realloc(buffer,
				(vector->current_size + vector->chunk_size) * vector->element_size);
		if (buffer == NULL)
			return false;
		vector->max_size += vector->chunk_size;
	}
	memmove(buffer + (ref + 1) * vector->element_size,
			buffer + ref * vector->element_size,
			(vector->current_size - ref) * vector->element_size);
	memcpy(buffer + ref * vector->element_size,
			element, vector->element_size);
	vector->current_size++;
	return true;
}

#endif

/*	Pesquisa sequencial
 *	retorna a posição onde encontrou ou a dimensão caso não tenha encontrado.
 */
bool vector_search(struct vector *vector, void *key,
					int (*compare)(const void *, const void *), size_t *index) {
	for (size_t i = 0; i < vector->current_size; ++i)
		if (compare(key, (char *)vector->buffer + i * vector->element_size)) {
			*index = i;
			return true;
		}
	return false;
}

/* retorna a dimensão do vetor
*/
size_t vector_size(struct vector *vector) {
	return vector->current_size;
}

/*	retorna o ponteiro para o elemento indicado
*/
void *vector_at(struct vector *vector, int index) {
	return (char *)vector->buffer + index * vector->element_size;
}

/*	Afetar uma posição do vetor
*/
void *vector_assign(struct vector *vector, int index, void *element) {
	if (vector->current_size <= index)
		vector->current_size = index + 1;
	/* falta verificar se é necessário alocar mais memória */
	return memcpy((char *)vector->buffer + index * vector->element_size,
				element, vector->element_size);
}

/*	Inserir elemento numa dada posição do vetor.
	Se a posição indica estiver além da dimensão atual, o vetor é aumentado.
	Retorna um booleano indicando o êxito da inserção.
*/
bool vector_insert(struct vector *vector, void *element, size_t index) {
	char *buffer = vector->buffer;
	if (index >= vector->current_size) {
		if (index >= vector->max_size) {
			vector->max_size = (index / vector->chunk_size + 1) * vector->chunk_size;
			vector->buffer = buffer = realloc(buffer, vector->max_size * vector->element_size);
			if (NULL == buffer)
				return false;
		}
		memcpy(buffer + index * vector->element_size, element, vector->element_size);
		vector->current_size = index + 1;
		return true;
	}
	/* index < vector->current_size */
	if (vector->current_size == vector->max_size) {
		vector->max_size += vector->chunk_size;
		vector->buffer = buffer = realloc(buffer, vector->max_size * vector->element_size);
		if (NULL == buffer)
			return false;
	}
	memmove(buffer + (index + 1) * vector->element_size,
			buffer +  index * vector->element_size,
			(vector->current_size - index) * vector->element_size);
	memcpy(buffer + index * vector->element_size, element, vector->element_size);
	vector->current_size++;
	return true;
}

/*	Elimina um elemento do vetor movendo os elementos das posições superiores para trás
*/
void vector_remove(struct vector *vector, size_t index) {
	memmove((char *)vector->buffer + index * vector->element_size,
		(char *)vector->buffer + (index + 1) * vector->element_size,
		(vector->current_size - index - 1) * vector->element_size);
	vector->current_size--;
}

/*	Ordenar o vetor
*/
void vector_sort(struct vector *vector, int (*compare)(const void *, const void *)) {
	qsort(vector->buffer, vector->current_size, vector->element_size, compare);
}

#if 0
/*	Remove o elemento indicado num vetor ordenado.
*	A remoção concretiza-se pelo recuo dos elementos seguintes.
*/
int vector_sorted_remove(struct vector *vector, void *element,
					int (*compare)(const void *, const void *)) {
	size_t left = 0, right = vector->current_size, middle = (right - left) / 2;
	void **buffer = vector->buffer;
	while (left < right) {
		int compare_result = compare(element, (char *)buffer + middle * vector->element_size);
		if (compare_result > 0)
			left = middle + 1;
		else if (compare_result < 0)
			right = middle;
		else {
			memmove((char *)buffer + middle * vector->element_size,
				(char *)buffer + (middle + 1) * vector->element_size,
				(vector->current_size - middle - 1) * vector->element_size);
			vector->current_size--;
			return 1;
		}
		middle = left + (right - left) / 2;
	}
	return 0;
}
#endif

/*	Percorre o vetor e para cada elemento invoca uma função de callback passando-o como argumento.
*/
void vector_foreach(struct vector *vector, void(*do_it)(void *, void *), void *context) {
	for (size_t i = 0; i < vector->current_size; ++i)
		do_it((char *)vector->buffer + i * vector->element_size, context);
}

#define VECTOR_TEST

#ifdef VECTOR_TEST

void print_int(void *data, void *context) {
	printf("%d + %d\n",  *(int*)context, *(int*)data);
}

int compare_int(const void *a, const void *b) {
	if (*(int*)a > *(int*)b)
		return 1;
	else if (*(int*)a < *(int*)b)
		return -1;
	return 0;
}

int main() {
	struct vector *v = vector_create(sizeof (int), 2);
	vector_insert(v,  &(int){10}, 0);
	vector_insert(v,  &(int){4}, 1);
	vector_insert(v,  &(int){5}, 2);
	vector_insert(v,  &(int){1}, 3);
	vector_foreach(v, print_int, &(int){10});
	putchar('\n');
	vector_sort(v, compare_int);
	vector_foreach(v, print_int, &(int){20});	
	putchar('\n');
	vector_destroy(v);

	int a = 3, b = 5, c = 4, d = 1;
	v = vector_create(sizeof (int), 2);
	size_t index;
	vector_sorted_search(v, &a, compare_int, &index);
	vector_insert(v, &a, index);
	vector_sorted_search(v, &b, compare_int, &index);
	vector_insert(v, &b, index);
	vector_sorted_search(v, &c, compare_int, &index);
	vector_insert(v, &c, index);
	vector_sorted_search(v, &d, compare_int, &index);
	vector_insert(v, &d, index);

	vector_foreach(v, print_int, &(int){30});
	putchar('\n');
	
	vector_sorted_search(v, &(int){3}, compare_int, &index);
	vector_remove(v, index);
	vector_foreach(v, print_int, &(int){30});
	putchar('\n');
	vector_destroy(v);
}

#endif
