/*
	Programa para simular uma fila de espera

	Utilização da lista pertencente à biblioteca Glib
	https://docs.gtk.org/glib/index.html

	struct GList - list duplamente ligada não intrusiva
*/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <glib.h>
/*-----------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
struct user {
	time_t arrival;
	char *name;
};

/*-----------------------------------------------------------------------------
	A fila de espera
 */
static GList *queue = NULL;

/*-----------------------------------------------------------------------------
	Função para insertir um novo utente na fila de espera
 */
static void user_insert(char *name)
{
	struct user *user = malloc(sizeof *user);
	if (NULL == user) {
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}
	user->name = malloc(strlen(name) + 1);
	if (NULL == user->name) {
		free(user);
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}
	strcpy(user->name, name);
	time(&user->arrival);
	queue = g_list_insert_before(queue, NULL, user);
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
char *user_answer()
{
	if (g_list_length(queue) == 0)
		return NULL;
	GList *node = g_list_first(queue);
	struct user *user = node->data;
	queue = g_list_delete_link(queue, node);
	char *name = user->name;
	free(user);
	return name;
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera, por desistencia
 */
static int name_compare(const void *a, const void *b)
{
	const struct user *user = a;
	const char *name = b;
	return strcmp(user->name, name);
}

static void user_remove(char *name)
{
	if (g_list_length(queue) == 0)
		return;
	GList *node = g_list_find_custom(queue, name, name_compare);
	if (node == NULL)
		return;
	struct user *user = node->data;
	queue = g_list_delete_link(queue, node);
	free(user->name);
	free(user);
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */
static void print(void *data, void *not_used)
{
	struct user *user = data;
	printf("Nome: %s, %ld\n", user->name, time(NULL) - user->arrival);
}

void user_print()
{
	if (g_list_length(queue) == 0) {
		printf("Fila vazia\n");
		return;
	}
	g_list_foreach(queue, print, NULL);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */

void free_user(void *user)
{
	free(((struct user *)user)->name);
	free(user);
}

void user_delete_queue()
{
	g_list_free_full(queue, free_user);
}

static void help()
{
	printf("Comandos:\n"
		"        S        - Sair do programa\n"
		"        H        - Mostrar lista de comando\n"
		"        N <name> - Chegada de novo utente\n"
		"        D <name> - Desistencia de utente\n"
		"        L        - Listar fila de espera\n"
		"        A        - Atender utente\n");
}

int main()
{
	char line[100];
	while (true) {
		if (fgets(line, sizeof(line), stdin) == NULL)
			return EXIT_FAILURE;
		char *command = strtok(line, " \n");
		if (command == NULL)
			continue;
		char *name = strtok(NULL, " \n");
		switch (toupper(*command)) {
			case 'S':
				user_delete_queue();
				return EXIT_FAILURE;
			case 'H':
				help();
				break;
			case 'N':
				user_insert(name);
				break;
			case 'D':
				user_remove(name);
				break;
			case 'L':
				user_print();
				break;
			case 'A':
				name = user_answer();
				if (NULL == name) {
					printf("Fila vazia\n");
				}
				else {
					printf("Atender %s\n", name);
					free(name);
				}
				break;
		}
	}
}
