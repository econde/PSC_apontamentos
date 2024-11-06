/*	Instituto Superior de Engenharia de Lisboa
	Ezequiel Conde, 2015
*/
#include <stdlib.h>
#include <assert.h>

#include "ilist.h"

void ilist_init(struct ilist_node *node)
{
	node->next = node->prev = node;
}

struct ilist_node *ilist_create()
{
	struct ilist_node *node = malloc(sizeof(struct ilist_node));
	if (node == 0)
		return 0;
	ilist_init(node);
	return node;
}

void ilist_destroy(struct ilist_node *list)
{
	assert(list);
	free(list);
}

/* node - elemento de referência; new_node - novo elemento */

void ilist_insert_front(struct ilist_node *list, struct ilist_node *new_node)
{
	assert(list && new_node);
	new_node->next = list->next;
	new_node->prev = list;
	list->next->prev = new_node;
	list->next = new_node;
}

void ilist_insert_rear(struct ilist_node *list, struct ilist_node *new_node)
{
	assert(list && new_node);
	new_node->prev = list->prev;
	new_node->next = list;
	list->prev->next = new_node;
	list->prev = new_node;
}

struct ilist_node *ilist_remove_front(struct ilist_node *list)
{
	assert(list);
	struct ilist_node *node = list->next;
	list->next = list->next->next;
	node->next->prev = node->prev;
	return node;
}

struct ilist_node *ilist_remove_rear(struct ilist_node *list)
{
	assert(list);
	struct ilist_node *node = list->prev;
	list->prev = list->prev->prev;
	node->prev->next = node->next;
	return node;
}

void ilist_remove(struct ilist_node *node)
{
	assert(node);
	if (node->next == node)
		return;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = node->prev = node;
}

int ilist_empty(struct ilist_node *list)
{
	assert(list);
	return list->next == list;
}

struct ilist_node *ilist_rear(struct ilist_node *node)
{
	assert(node);
	return node->prev;
}

struct ilist_node *ilist_front(struct ilist_node *list)
{
	assert(list);
	return list->next;
}

struct ilist_node *ilist_sentinel(struct ilist_node *list)
{
	assert(list);
	return list;
}

struct ilist_node *ilist_search(struct ilist_node *list,
	int (*cmp)(struct ilist_node *, const void *), const void *key)
{
	for (struct ilist_node *node = list->next; node != list; node = node->next)
		if (cmp(node, key) == 0)
			return node;
	return NULL;
}

void ilist_foreach(struct ilist_node *list,
	void (*do_it)(struct ilist_node *, void *context), void *context)
{
	for (struct ilist_node *next, *node = list->next; node != list; node = next) {
		next = node->next;
		do_it(node, context);
	}
}

int ilist_size(struct ilist_node *list)
{
	int counter = 0;
	struct ilist_node * link;
	for (link = ilist_front(list);
			link != ilist_sentinel(list); link = ilist_front(link))
		counter++;
	return counter;
}
