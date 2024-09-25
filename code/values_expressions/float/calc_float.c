#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>

/*	Número de casas fracionárias em binário
 */
#define BIN_FRAC	23

/*	Número de casas fracionárias em decimal - casas decimais
 */
#define DEC_FRAC	2

typedef union {
	int i;
	float f;
	struct {
		unsigned int mantissa: 23;
		unsigned int exponent: 8;
		unsigned int signal: 1;
	};
} Float;

int get_msb_position(long value) {
	int p = 0;
	while (value > 1) {
		value >>= 1;
		p++;
	}
	return p;
}

float string_to_float(char *string) {
	if (*string == 0 || strcmp(string, "0.0") == 0)
		return 0.0;
	long value = 0;
	/* parte inteira */
	while (*string != '.') {
		int digit = *string++ - '0';
		value = value * 10 + digit;
	}
	string++;	/* ponto */
	int exp_dec = 0;
	/* parte fracionária */
	while (*string != 0) {
		int digit = *string++ - '0';
		value = value * 10 + digit;
		exp_dec -= 1;
	}

	/* colocar bit mais significativo na posição 60 de value
	 * para se poder reduzir o expoente decimal com o mínimo de erro */
	int msb_position = get_msb_position(value);
	int exp_bin = msb_position;
	if (msb_position > 60)
		value >>= (msb_position - 60);
	else
		value <<= (60 - msb_position);

	/* reduzir o expoente decimal */
	while (exp_dec < 0) {
		while ((value & (1L << 63)) != 0) {
			value <<= 1;
			exp_bin--;
		}
		value /= 10;
		exp_dec++;
	}

	/* normalizar 1,------- */
	while ((value & (~0L << 60)) == 0) {
		value <<= 1;
		exp_bin--;
	}

	Float result = {.exponent = exp_bin + 127, .mantissa = value >> (60 - 23)};
	return result.f;
}

void float_print_bin(float f)  {
	Float value = {.f = f};

	putchar(value.signal ? '1' : '0');
	putchar(' ');
	for (int i = 7; i >= 0; --i)
		putchar(value.exponent & (1 << i) ? '1' : '0');
	putchar(' ');
	for (int i = 22; i >= 0; --i)
		putchar(value.mantissa & (1 << i) ? '1' : '0');
	putchar('\n');
}

void float_to_string(float value, char buffer[], size_t buffer_size) {
	Float x = { .f = value };
	long y = (1L << 23) | x.mantissa;
	if (x.exponent > 127)
		y <<= x.exponent - 127;
	else
		y >>= 127 - x.exponent;

	y *= 1000000;
	y >>= 23;

	int i = 0;
	while (y > 0) {
		buffer[i++] = y % 10 + '0';
		y /= 10;
		if (i == 6)
			buffer[i++] = '.';
	}
	buffer[i] = 0;
	int j = 0;
	for (i--; j < i; i--, j++) {
		char tmp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = tmp;
	}
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "usage: %s <operand1> <operation> <operand2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	float op1 = string_to_float(argv[1]);
	printf("%f ", op1); float_print_bin(op1);
	float op2 = string_to_float(argv[3]);
	printf("%f ", op2); float_print_bin(op2);
	float result;
	switch (argv[2][0]) {
		case '+':
			result = op1 + op2;
			break;
		case '-':
			result = op1 - op2;
			break;
		case 'x':
			result = op1 * op2;
			break;
		case '/':
			result = op1 / op2;
			break;
	}
	printf("%f ", result);
	float_print_bin(result);
	char string_result[20];
	float_to_string(result, string_result, sizeof string_result);
	printf("%s\n", string_result);
}
