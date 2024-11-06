#include <glib.h>
#include <stdio.h>
#include <stdbool.h>


static gint word_compare(gconstpointer a, gconstpointer b)  {
	return strcmp(*(char **) a, *(char **) b);
}

static void word_print(gpointer data, gpointer user_data) {
	puts((char *) data);
}

int main(int argc, char *argv[]) {
	GPtrArray *array = g_ptr_array_new();
#if 0
	g_ptr_array_insert(array, 0, "Filipa");
	g_ptr_array_insert(array, 1, "Maria");
	g_ptr_array_insert(array, 2, "Ana");

	g_ptr_array_foreach(array, word_print, NULL);
	g_ptr_array_sort(array, word_compare);
	g_ptr_array_foreach(array, word_print, NULL);
#endif
	g_ptr_array_free(array, true);
}
