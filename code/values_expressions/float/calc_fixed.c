#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*	Número de casas fracionárias em binário
 */
#define BIN_FRAC	6

/*	Número de casas fracionárias em décimal - casas décimais 
 */
#define DEC_FRAC	2

unsigned long string_to_real(char string[]) {
	unsigned long value = 0;
	int i;
	for (i = 0; string[i] != '.'; ++i) {
		int digit = (string[i] - '0') << BIN_FRAC;
		value = value * 10 + digit;
	}
	int fraction = 1;
	for (++i; string[i] != 0; ++i) {
		int digit = (string[i] - '0') << BIN_FRAC;
		value = value * 10 + digit;
		fraction *= 10;
	}
	return value / fraction;
}

void real_to_string(unsigned long value, char buffer[], size_t buffer_size) {
	if (value == 0) {
		strncpy(buffer, "0.0", buffer_size);
		return;
	}
	int i;
	for (i = 0; i < DEC_FRAC; ++i)
		value *= 10;
	value >>= BIN_FRAC;

	for (i = 0; (value > 0 || i < DEC_FRAC) && i < buffer_size - i; ++i) {
		buffer[i] = value % 10 + '0';
		value /= 10;
		if (i == 1)
			buffer[++i] = '.';
	}
	buffer[i--] = 0;
	/* inverter */
	for (int j = 0; j < i; ++j, --i) {
		char tmp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = tmp;
	}
}

int main(int argc, char *argv[]) {

	if (argc != 4) {
		fprintf(stderr, "usage: %s <operand1> <operation> <operand2>\n", argv[0]);
		exit(0);
	}
	printf("op1 = %s\n", argv[1]);
	printf("opr = %s\n", argv[2]);
	printf("op2 = %s\n", argv[3]);

	unsigned long op1 = string_to_real(argv[1]);
	unsigned long op2 = string_to_real(argv[3]);
	unsigned long result;
	switch (argv[2][0]) {
		case '+':
			result = op1 + op2;
			break;
		case '-':
			result = op1 - op2;
			break;
		case 'x':
			result = op1 * op2;
			result >>= BIN_FRAC;
			break;
		case '/':
			op1 <<= BIN_FRAC;
			result = op1 / op2;
			break;
	}
	printf("op1 = %lx\nop2 = %lx\nresult=%lx\n", op1, op2, result);
	char string_result[20];
	real_to_string(result, string_result, sizeof string_result);
	printf("%s\n", string_result);
}
