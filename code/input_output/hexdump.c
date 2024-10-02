#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	FILE *fd = stdin;
	if (argc > 1) {
		fd = fopen(argv[1], "rb");
		if (fd == NULL) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			return EXIT_FAILURE;
		}
	}
	char buffer[16];
	size_t n_bytes = fread(buffer, 1, sizeof buffer, fd);
	while (n_bytes > 0) {
		for (size_t i = 0; i < n_bytes; i++)
			printf("%02x ", (unsigned char) buffer[i]);
		putchar(' ');
		for (size_t i = 0; i < n_bytes; i++)
			printf("%c", isalnum(buffer[i]) | buffer[i] == ' ' ? buffer[i] : '.');
		putchar('\n');
		n_bytes = fread(buffer, 1, sizeof buffer, fd);
	}
	fclose(fd);
}
