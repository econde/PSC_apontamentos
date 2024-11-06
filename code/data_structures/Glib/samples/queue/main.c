#include <glib.h>
#include <stdio.h>
#include <stdbool.h>


static gint word_compare(gconstpointer a, gconstpointer b, gpointer not_used)  {
	return -strcmp((char *) a, (char *) b);
}

static void word_print(gpointer data, gpointer user_data) {
	puts((char *) data);
}

int main(int argc, char *argv[]) {
	GQueue *queue = g_queue_new();

	g_queue_push_tail(queue, "Filipa");
	g_queue_push_tail(queue, "Maria");
	g_queue_push_head(queue, "Ana");

	g_queue_foreach(queue, word_print, NULL);
	g_queue_sort(queue, word_compare, NULL);
	g_queue_foreach(queue, word_print, NULL);

	g_queue_free(queue);
}
