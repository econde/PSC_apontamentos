#include <glib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	GHashTable* hash = g_hash_table_new(g_str_hash, g_str_equal);

	g_hash_table_insert(hash,"Ana","azul");
	g_hash_table_insert(hash,"Maria","verde");

	printf("A hash table tem %d entradas\n", g_hash_table_size(hash));

	char *name = "Ana";
	printf("%s gosta de %s\n", name, (char *)g_hash_table_lookup(hash, name));

	g_hash_table_destroy(hash);
}
