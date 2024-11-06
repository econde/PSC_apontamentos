#include <stdio.h>
#include <stdbool.h>

#include <glib.h>

static gint number_compare(gconstpointer a, gconstpointer b)  {
	return strcmp((char *) a, (char *) b) == 0;
}

static guint hash_function(gconstpointer ordinal_number) {
	guint a = 0;
	char c;
	do {
		c = *(char *)ordinal_number++;
		a = (a << 1) + c;
	} while ( c != 0);
	return a;
}

int main(int argc, char *argv[]) {
	FILE *fd = fopen(argv[1], "r");
	GHashTable *table = g_hash_table_new(hash_function, number_compare);
	unsigned number;
	char ordinal_array[100];
	int result = fscanf(fd, "%u %[^\n]", &number, ordinal_array);
	while (result == 2) {
		unsigned  *pnumber = malloc(sizeof *pnumber);
		*pnumber = number;
		gboolean not_exist = g_hash_table_insert(table, strdup(ordinal_array), pnumber);
		if (!not_exist)
			printf("g_hash_table_insert(), key %s already exist\n", ordinal_array);
		result = fscanf(fd, "%u %[^\n]", &number, ordinal_array);
	}
	while (true) {
		char dummy;
		printf("Number? ");
		scanf("%[^\n]%c", ordinal_array, &dummy);
		printf("%s\n", ordinal_array);
		if (strcmp("-1", ordinal_array) == 0)
			return 0;
		unsigned *pnumber = g_hash_table_lookup(table, ordinal_array);
		if (pnumber != NULL)
			printf("%u %s\n", *pnumber, ordinal_array);
	}
}
