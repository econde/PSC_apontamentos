/*
	+---+---+---+---+---+---+---+---+---+---+---+---*
	| n |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---*
		  ^
		  ap
*/

#include <stdarg.h>

int sum(int n, ...) {
	if (n <= 0)
		return 0;
	va_list ap;

	va_start(ap, n);				/* ap = &n + 1 */
	int result = va_arg(ap, int);	/* *((int *)ap++) */
	for (int i = 1; i < n; ++i)
		 result += va_arg(ap, int);
	return result;
}

int main() {
	int a = sum(2, 10, 10);
	int b = sum(3, 10, 20, 30);
}
