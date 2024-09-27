#include <string.h>
#include <stdio.h>

#define ARRAY_SIZE(a)	(sizeof (a) / sizeof (a)[0])

void swap(char a[], char b[]) {
	size_t i;
	for (i = 0; a[i] != 0 && b[i] != 0; ++i) {
		char tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
	if (a[i] == 0) {
		for (; b[i] != 0 ; ++i)
			a[i] = b[i];
		a[i] = 0;
	}
	else {
		for (; a[i] != 0 ; ++i)
			b[i] = a[i];
		b[i] = 0;
	}
}

void sort(char array[][100], int size) {
	for (size_t i = 0; i < size - 1; ++i)
		for (size_t j = 0; j < size - i - 1; ++j)
			if (strcmp(array[j], array[j + 1]) > 0)
				swap(array[j], array[j + 1]);
}

void print(char array[][100], size_t size) {
	putchar('\n');
	for (size_t i = 0; i < size; ++i)
		printf("%s\n", array[i]);
}

char names[][100] = {
	"antonio manuel",
	"joaquim antunes",
	"manuel francisco",
	"luis alfredo"
};

int main() {
	print(names, ARRAY_SIZE(names));
	sort(names, ARRAY_SIZE(names));
	print(names, ARRAY_SIZE(names));
}
