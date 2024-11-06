#ifndef ILIST_H
#define ILIST_H

struct ilist_node {
	struct ilist_node *next, *prev;
};

#define STATIC_LIST(name) struct ilist_node name = {&name, &name};

void ilist_init(struct ilist_node *node);

struct ilist_node *ilist_create();

void ilist_destroy(struct ilist_node *list);

void ilist_insert_rear(struct ilist_node *list, struct ilist_node *new_node);

void ilist_insert_front(struct ilist_node *list, struct ilist_node *new_node);

struct ilist_node *ilist_remove_rear(struct ilist_node *list);

struct ilist_node *ilist_remove_front(struct ilist_node *list);

void ilist_remove(struct ilist_node *node);

int ilist_empty(struct ilist_node *list);

struct ilist_node *ilist_get_front(struct ilist_node *list);

struct ilist_node *ilist_get_rear(struct ilist_node *list);

struct ilist_node *ilist_sentinel(struct ilist_node *list);

struct ilist_node *ilist_search(struct ilist_node *list,
		int (*cmp)(struct ilist_node *, const void *), const void *context);

void ilist_foreach(struct ilist_node *node,
	void (*do_it)(struct ilist_node *, void *context), void *context);

int ilist_size(struct ilist_node *list);

#endif
