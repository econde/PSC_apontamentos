#include <stdio.h>
#include <limits.h>

typedef union {
	float f;
	unsigned int i;
} Float;

int main() {
	Float x = {.f = 30.4375};

	int bit = sizeof x.i * CHAR_BIT - 1;

	putchar((x.i & (1 << bit)) == 0 ? '0' : '1');       /* sinal */
	putchar(' ');
	for (--bit; bit >= 23; --bit)                       /* expoente */
		putchar((x.i & (1 << bit)) == 0 ? '0' : '1');
	putchar(' ');
	for ( ; bit >= 0; --bit)                            /* mantissa */
		putchar((x.i & (1 << bit)) == 0 ? '0' : '1');
	putchar('\n');
}
