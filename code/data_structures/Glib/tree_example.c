#include <stdio.h>
#include <stdbool.h>

#include <glib.h>

static gint number_compare(gconstpointer a, gconstpointer b)  {
	if (*(unsigned *) a > *(unsigned *) b)
		return +1;
	if (*(unsigned *) a < *(unsigned *) b)
		return -1;
	return 0;
}

int main(int argc, char *argv[]) {
	FILE *fd = fopen(argv[1], "r");
	GTree *tree = g_tree_new(number_compare);
	unsigned number;
	char ordinal_array[100];
	int result = fscanf(fd, "%u  %[^\n]", &number, ordinal_array);
	while (result == 2) {
		unsigned  *pnumber = malloc(sizeof *pnumber);
		*pnumber = number;
		g_tree_insert(tree, pnumber, strdup(ordinal_array));
		result = fscanf(fd, "%u %[^\n]", &number, ordinal_array);
	}
	while (true) {
		printf("Number? ");
		scanf("%u", &number);
		if (number == -1)
			return 0;
		GTreeNode *tn = g_tree_lookup_node(tree, &number);
		if (tn != NULL)
			printf("%u %s\n", *(unsigned*) g_tree_node_key(tn), (char *)g_tree_node_value(tn));
	}
}
