/*
	Programa para gerir uma lista de tarefas

	Objectivo: exemplificar a utilização de uma lista ligada
				e a alocação dinâmica de memória.

	Criando diretamente uma lista simplesmente ligada
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*-----------------------------------------------------------------------------
	Representa um utente na fila de espera
 */
typedef struct task {
	struct task *next;
	int priority;
	char *desc;
} Task;

/*-----------------------------------------------------------------------------
	A lista é representada por estes dois ponteiros
 */
static Task *head = NULL, *tail = NULL;

/*-----------------------------------------------------------------------------
	Função para insertir um novo utente na fila de espera
 */
static void task_insert(char *desc) {
	Task *task = malloc(sizeof *task);
	if (NULL == task) {
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}
	task->desc = malloc(strlen(desc) + 1);
	if (NULL == task->desc) {
		free(task);
		fprintf(stderr, "Out of memory\n");
		exit(-1);
	}
	strcpy(task->desc, desc);
	task->next = NULL;
	if (NULL == head)
		head = tail = task;
	else {
		tail->next = task;
		tail = task;
	}
}

/*-----------------------------------------------------------------------------
	Função para remover da lista a próxima tarefa a ser executada
 */
char *task_next() {
	if (NULL == head)
		return NULL;
	Task *task = head;
	head = head->next;
	tail = NULL == head ? NULL : tail;

	char *desc = task->desc;
	free(task);
	return desc;
}

/*-----------------------------------------------------------------------------
	Função para remover uma dada tarefa da lista
 */
static void task_remove(char *desc) {
	if (NULL == head)
		return;
	Task *prev = NULL;
	for (Task *task = head; task != NULL; prev = task, task = task->next)
		if (strcmp(desc, task->desc) == 0){
			if (NULL == prev) {
				head = task->next;
				tail = NULL == head ? NULL : tail;
			}
			else {
				prev->next = task->next;
				tail = NULL == prev->next ? prev : tail;
			}
			free(task->desc);
			free(task);
			return;
		}
}

/*-----------------------------------------------------------------------------
	Listar as tarefas
 */
void task_print() {
	if (NULL == head) {
		printf("Fila vazia\n");
		return;
	}
	int i = 1;
	for (Task *task = head; task != NULL; task = task->next)
		printf("%d: %s, %d\n", i++, task->desc, task->priority);
}

/*-----------------------------------------------------------------------------
	Vazar a lista libertando toda a memória alocada.
 */
void task_leak_list() {
	for (Task *next, *p = head; p != NULL; p = next) {
		next = p->next;
		free(p->desc);
		free(p);
	}
}

static void help() {
	printf("Comandos:\n"
		"\tS\t\t- Sair\n"
		"\tI <desc> \t- Insersão de nova tarefa\n"
		"\tR <desc>\t- Remover uma tarefa\n"
		"\tL\t\t- Listar alista de tarefas\n"
		"\tA\t\t- Cumprir uma tarefa\n");
}

int main() {
	char line[100];
	while (1) {
		if (fgets(line, sizeof(line), stdin) == NULL)
			exit(1);
		char * command = strtok(line, " \n");
		char * desc = strtok(NULL, " \n");
		switch (command[0]) {
			case 's':
			case 'S':
				task_leak_list();
				exit(0);
			case 'h':
			case 'H':
				help();
				break;
			case 'n':
			case 'N':
				task_insert(desc);
				break;
			case 'd':
			case 'D':
				task_remove(desc);
				break;
			case 'l':
			case 'L':
				task_print();
				break;
			case 'c':
			case 'C':
				desc = task_next();
				if (NULL == desc)
					printf("Lista vazia\n");
				else {
					printf("Realizar: %s\n", desc);
					free(desc);
				}
				break;
		}
	}
}


