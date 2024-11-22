#include <stdio.h>

extern void *_init;
extern void *_start;
extern void *__data_start;
extern void *_edata;
extern void *__bss_start;
extern void *_end;

void *get_sp();

void recurse() {
	char array[1024 * 1024];
	printf("%p\n", get_sp());
	recurse();
}

int main() {

	printf("       _init: %p\n", &_init);
	printf("      _start: %p\n", &_start);
	printf("        main: %p\n", main);
	printf("__data_start: %p\n", &__data_start);
	printf("      _edata: %p\n", &_edata);
	printf(" __bss_start: %p\n", &__bss_start);
	printf("        _end: %p\n", &_end);
	printf("         rsp: %p\n", get_sp());
	getchar();
	recurse();
}
