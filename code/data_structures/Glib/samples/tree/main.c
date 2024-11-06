#include <glib.h>
#include <stdio.h>

static gint word_compare(gconstpointer a, gconstpointer b)  {
	return strcmp((char *) a, (char *) b);
}

int main(int argc, char *argv[]) {
	GTree *tree = g_tree_new(word_compare);

	g_tree_insert(tree,"Ana", "azul");
	g_tree_insert(tree,"Maria", "verde");

	printf("A árvore tem %d nós\n", g_tree_nnodes(tree));

	char *name = "Ana";
	printf("%s gosta de %s\n", name, (char *)g_tree_lookup(tree, name));

	g_tree_destroy(tree);
}
