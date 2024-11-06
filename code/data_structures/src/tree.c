#include <stdlib.h>
#include "tree.h"

void tree_destroy(struct tree_node *node) {
	if (NULL == node)
		return;
	tree_destroy(node->left);
	tree_destroy(node->right);
	free(node);
}

struct tree_node *tree_search(struct tree_node *node, const void *key,
					int(*compare)(const void*, const void*)) {
	if (NULL == node)
		return NULL;
	int cmp_result = compare(node->data, key);
	if (cmp_result == 0)
		return node;
	if (cmp_result < 0)
		return tree_search(node->right, data, cmp);
	else
		return tree_search(node->left, data, cmp);
}

struct tree_node *tree_insert(struct tree_node *root, void *data,
					int (*compare)(const void*, const void*)) {
	if (NULL == root) {
		struct tree_node *new_node = malloc(sizeof *new_node);
		if (NULL == new_node)
			return NULL;
		new_node->left = new_node->right = NULL;
		new_node->data = data;
		return new_node;
	}
	int cmp_result = compare(root->data, data);
	if (cmp_result < 0)
		root->right = tree_insert(root->right, data, cmp);
	else if (cmp_result > 0)
		root->left = tree_insert(root->left, data, cmp);
	return root;
}

size_t tree_size(struct tree_node *node)  {
	if (NULL == node)
		return 0;
	return tree_size(node->left) + tree_size(node->right) + 1;
}

void tree_foreach(struct tree_node *node, void (*do_it)(void *)) {
	if (NULL == node)
		return;
	tree_foreach(node->left, do_it);
	do_it(node->data);
	tree_foreach(node->right, do_it);
}

static inline int max(int a, int b) {
	return (a > b) ? a : b;
}

int tree_depth(struct tree_node *node) {
	if (node == NULL)
		return 0;
	return max(tree_depth(node->left), tree_depth(node->right)) + 1;
}

void *tree_data(struct tree_node *node) {
	return node->data;
}
