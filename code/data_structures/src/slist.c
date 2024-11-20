#include <stdlib.h>
#include "slist.h"

struct slist_node {
	struct slist_node *next;
	void *data;
};

void slist_destroy(struct slist_node *list) {
	for (struct slist_node *next, *p = list; p != NULL; p = next) {
		next = p->next;
		free(p);
	}
}

struct slist_node *slist_insert_sort(struct slist_node *list,
	int (*fcmp)(const void *, const void *), void *data) {
	struct slist_node *node = malloc(sizeof (*node));
	if (NULL == node)
		return NULL;
	node->data = data;
	node->next = NULL;
	if (list == NULL)						/*	Primeiro elemento */
		;
	else if (fcmp(list->data, data) > 0) {	/* Inserção antes do primeiro elemento */
		node->next = list;
	}
	else {
		struct slist_node *prev = list;		/* Primeiro elemento já verificado */
		struct slist_node *p;
		for (p = prev->next; p != NULL && fcmp(p->data, data) < 0; prev = p, p = p->next)
			;
		node->next = p;
		prev->next = node;
		return list;
	}
	return node;
}

struct slist_node *slist_insert(struct slist_node *list, void *data) {
	struct slist_node *node = malloc(sizeof (*node));
	if (NULL == node)
		return 0;
	node->data = data;
	node->next = list;
	return node;
}

struct slist_node *slist_remove_head(struct slist_node *list) {
	struct slist_node *next = list->next;
	free(list);
	return next;
}

struct slist_node *slist_remove(struct slist_node *list, struct slist_node *node) {
	if (node == NULL || list == NULL)
		return list;
	if (list == node) {
		list = node->next;
		free(node);			/* Remover o primeiro elemento */
	}
	else {
		struct slist_node *prev = list;
		for (struct slist_node *p = prev->next; p != NULL; prev = p, p = p->next)
			if (p == node) {
				prev->next = node->next;
				free(node);
			}
	}
	return list;
}

void slist_foreach(struct slist_node *list, void(*do_it)(void *, void *), void *context) {
	for (struct slist_node * p = list; p != NULL; p = p->next)
		do_it(p->data, context);
}

struct slist_node *slist_search_sort(struct slist_node *list,
							int (*fcmp)(const void *, const void *), const void *data) {
	for (struct slist_node *p = list; p != NULL; p = p->next) {
		int tmp = fcmp(p->data, data);
		if (tmp == 0)
			return p;
		else if (tmp > 0)
			return NULL;
	}
	return NULL;
}

struct slist_node *slist_search(struct slist_node *list, const void *data,
	int (*fcmp)(const void *, const void *)) {
	for (struct slist_node *p = list; p != NULL; p = p->next)
		if (fcmp(p->data, data) == 0)
			return p;
	return NULL;
}

int slist_size(struct slist_node *list) {
	int n = 0;
	for (struct slist_node *p = list; p != NULL; p = p->next, ++n)
		;
	return n;
}

void *slist_data(struct slist_node *node) {
	return node->data;
}

int slist_empty(struct slist_node *list) {
	return NULL == list;
}

