#include <stdio.h>

void *get_start();

int main() {
	printf("_start = %p\n", get_start());
}
