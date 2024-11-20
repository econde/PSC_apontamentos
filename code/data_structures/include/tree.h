#ifndef TREE_H
#define TREE_H

struct tree_node;

void tree_destroy(struct tree_node *);

struct tree_node *tree_insert(struct tree_node *node, void *data,
					int (*cmp)(const void *, const void *));

struct tree_node *tree_search(struct tree_node *node, const void *key,
					int (*cmp)(const void *, const void *));

void tree_foreach(struct tree_node *node, void (*do_it)(void*));

size_t tree_size(struct tree_node *node);

int tree_depth(struct tree_node *node);

void *tree_data(struct tree_node *);

#endif





