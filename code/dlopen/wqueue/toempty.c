#include <stdlib.h>
#include "user.h"

extern struct user queue;

void command_function(char *name) {
	struct user *next;
	for (struct user *p = queue.next; p != &queue; p = next) {
		next = p->next;
		free(p->name);
		free(p);
	}
	queue.next = queue.prev = &queue;
}

char command_letter = 'k';

char *command_description = "\t - Eliminar todos os utentes da fila de espera";
