#ifndef SLIST_H
#define SLIST_H

#define STATIC_LIST(name)	struct slist_node *name = NULL;

struct slist_node;

//static inline void slist_init(struct slist_node *list) { list->next = list; }

void slist_destroy(struct slist_node *list);

struct slist_node *slist_insert(struct slist_node *list, void *data);

struct slist_node *slist_remove(struct slist_node *list, struct slist_node *node);

struct slist_node *slist_remove_head(struct slist_node *list);

struct slist_node *slist_insert_sort(struct slist_node *list,
	int (*cmp)(const void *, const void *), void *data);

void slist_foreach(struct slist_node *list, void(*do_it)(void*, void *), void *context);

struct slist_node *slist_search_sort(struct slist_node *list,
	int (*fcmp)(const void *, const void *), const void *data);

struct slist_node *slist_search(struct slist_node *list, const void *data,
	int (*cmp)(const void *, const void *));

int slist_size(struct slist_node *);

void *slist_data(struct slist_node *);

int slist_empty(struct slist_node *);

#endif
