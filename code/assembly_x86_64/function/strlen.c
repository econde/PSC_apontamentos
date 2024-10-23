#include <stdlib.h>

size_t strlen(char string[]) {
	size_t len;
	for (len = 0; string[len] != '\0'; ++len)
		;
	return len;
}
