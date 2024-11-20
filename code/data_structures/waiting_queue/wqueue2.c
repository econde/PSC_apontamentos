/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista ligada
				e a alocação dinâmica.

	Criando diretamente uma lista intrusiva duplamente ligada com sentinela
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
/*-----------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
struct user {
	struct user *next, *prev;
	time_t arrival;
	char *name;
};

/*-----------------------------------------------------------------------------
	A fila de espera é representada por elemento struct user, usado como sentinela
 */
static struct user queue = { .next = &queue, .prev = &queue };

/*-----------------------------------------------------------------------------
	Função para insertir um novo utente na fila de espera
 */
static void user_insert(char *name)
{
	struct user *user = malloc(sizeof *user);
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

	user->prev = queue.prev;
	user->next = &queue;
	queue.prev->next = user;
	queue.prev = user;
}

/*-----------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
char *user_answer()
{
	if (queue.next == &queue)
		return NULL;
	struct user *user = queue.next;

	user->next->prev = user->prev;
	user->prev->next = user->next;

	char *name = user->name;
	free(user);
	return name;
}

/*-----------------------------------------------------------------------------
	Função para remover um utente da fila de espera por desistência
 */
static void user_remove(char *name)
{
	for (struct user *user = queue.next; user != &queue; user = user->next)
		if (strcmp(name, user->name) == 0) {

			user->prev->next = user->next;
			user->next->prev = user->prev;

			free(user->name);
			free(user);
			return;
		}
}

/*-----------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */
void user_print()
{
	if (queue.next == &queue) {
		printf("Fila vazia\n");
		return;
	}
	int i = 1;
	for (struct user *user = queue.next; user != &queue; user = user->next)
		printf("%d: %s, %ld\n", i++, user->name, time(NULL) - user->arrival);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */
void user_delete_queue()
{
	for (struct user *next, *p = queue.next; p != &queue; p = next) {
		next = p->next;
		free(p->name);
		free(p);
	}
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


