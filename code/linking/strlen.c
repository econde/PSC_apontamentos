#include <stdlib.h>

size_t strlen(const char *str) {
	size_t length = 0;
	while (*str++)
		++length;
	return length;
}
