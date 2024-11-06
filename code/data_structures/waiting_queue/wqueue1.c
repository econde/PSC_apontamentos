/*
	Programa para simular uma fila de espera

	Objectivo: exemplificar a utilização de uma lista ligada
			e a alocação dinâmica.

	Utilização direta de lista simplesmente ligada
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*------------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
struct user {
	struct user *next;	/* Próximo elemento na lista (fila) */
	time_t arrival;		/* Momento da chegada */
	char *name;		/* Nome do utente */
};

/*------------------------------------------------------------------------------
	A fila de espera é representada por estes dois ponteiros
 */
static struct user *head = NULL, *tail;

/*------------------------------------------------------------------------------
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
	user->next = NULL;
	if (NULL == head)
		head = tail = user;
	else {
		tail->next = user;
		tail = user;
	}
}

/*------------------------------------------------------------------------------
	Função para remover da fila o primeiro utente a ser atendido
 */
static char *user_answer()
{
	if (NULL == head)
		return NULL;
	struct user *user = head;
	head = head->next;

	char *name = user->name;
	free(user);
	return name;
}

/*------------------------------------------------------------------------------
	Função para remover um utente da fila de espera, por desistencia
 */
static void user_remove(char *name)
{
	if (NULL == head)
		return;
	struct user *prev = NULL;
	for (struct user *user = head; user != NULL; prev = user, user = user->next)
		if (strcmp(name, user->name) == 0) {
			if (NULL == prev) {
				head = user->next;
			}
			else {
				prev->next = user->next;
				if (NULL == prev->next)
					tail = prev;
			}
			free(user->name);
			free(user);
			return;
		}
}

/*------------------------------------------------------------------------------
	Listar os utentes na fila de espera.
 */
static void user_print()
{
	if (NULL == head) {
		printf("Fila vazia\n");
		return;
	}
	int i = 1;
	for (struct user *user = head; user != NULL; user = user->next)
		printf("%d: %s, %ld\n", i++, user->name, time(NULL) - user->arrival);
}

/*------------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */
static void user_delete_queue()
{
	for (struct user *next, *user = head; user != NULL; user = next) {
		next = user->next;
		free(user->name);
		free(user);
	}
}

static void help()
{
	printf("Comandos:\n"
		"\tS\t\t- Sair do programa\n"
		"\tH\t\t- Mostrar lista de comando\n"
		"\tN <name>\t- Chegada de novo utente\n"
		"\tD <name>\t- Desistencia de utente\n"
		"\tL\t\t- Listar fila de espera\n"
		"\tA\t\t- Atender utente\n");
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
		switch (command[0]) {
			case 's':
			case 'S':
				user_delete_queue();
			return EXIT_FAILURE;
				return ;
			case 'h':
			case 'H':
				help();
				break;
			case 'n':
			case 'N':
				user_insert(name);
				break;
			case 'd':
			case 'D':
				user_remove(name);
				break;
			case 'l':
			case 'L':
				user_print();
				break;
			case 'a':
			case 'A':
				name = user_answer();
				if (NULL == name)
					printf("Fila vazia\n");
				else {
					printf("Atender %s\n", name);
					free(name);
				}
				break;
		}
	}
}


