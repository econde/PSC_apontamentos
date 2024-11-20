/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista ligada
		e a alocação dinâmica.

	Usando lista não intrusiva duplamente ligada com sentinela
	implementada em separado
*/
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"

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
static struct list_node *queue;

/*-----------------------------------------------------------------------------
	Função para insertir um novo utente na fila de espera
 */
static void user_insert(char *name)
{
	struct user * user = malloc(sizeof *user);
	if (NULL == user) {
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
	user->name = malloc(strlen(name) + 1);
	if (NULL == user->name) {
		free(user);
		fprintf(stderr, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
	strcpy(user->name, name);
	time(&user->arrival);
	list_insert_rear(queue, user);
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
char *user_answer()
{
	if (list_empty(queue))
		return NULL;
	struct list_node *node = list_get_front(queue);
	struct user *user = list_get_data(node);
	list_remove(node);

	char *name = user->name;
	free(user);
	return name;
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera, por desistencia
 */
static bool name_compare(const void *a, const void *b)
{
	const struct user *user = a;
	const char *name = b;
	return strcmp(user->name, name) == 0;
}

static void user_remove(char *name)
{
	if (list_empty(queue))
		return;
	struct list_node *node = list_search(queue, name_compare, name);
	if (node == NULL)
		return;
	struct user *user = list_get_data(node);
	list_remove(node);
	free(user->name);
	free(user);
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */

static void print(void *a, void *)
{
	struct user *user = a;
	printf("Nome: %s, %ld\n", user->name, time(NULL) - user->arrival);
}

void user_print()
{
	if (list_empty(queue)) {
		printf("Fila vazia\n");
		return;
	}
	list_foreach(queue, print, NULL);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */

void free_user(void *data, void *)
{
	struct user *user = data;
	free(user->name);
	free(user);
}

void user_delete_queue()
{
	list_foreach(queue, free_user, NULL);
	list_destroy(queue);
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
