#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
	char *arg_a = NULL, *arg_c = NULL;
	bool d = false, e = false;
	bool error_in_options = false;

	for (int i = 0; i < argc; ++i)
		printf("argv[%d] = %s\n", i, argv[i]);
	printf("------------------------------------\n");

	int opt;
	while ((opt = getopt(argc, argv, "a:c:de")) != -1) {
		switch(opt) {
		case 'a':
			arg_a = optarg;
			break;
		case 'c':
			arg_c = optarg;
			break;
		case 'd':
			d = true;
			break;
		case 'e':
			e = true;
			break;
		case '?':
			error_in_options = true;
		}
	}
	if (error_in_options)
		exit(EXIT_FAILURE);

	printf("Argumento da opção a: %s\n", arg_a);
	printf("Argumento da opção c: %s\n", arg_c);
	printf("Opção d: %b\n", d);
	printf("Opção e: %b\n", e);
	printf("Restantes argumentos:");
	for (int i = optind; i < argc; ++i)
		printf(" %s", argv[i]);
	putchar('\n');

	printf("------------------------------------\n");
	for (int i = 0; i < argc; ++i)
		printf("argv[%d] = %s\n", i, argv[i]);
}
