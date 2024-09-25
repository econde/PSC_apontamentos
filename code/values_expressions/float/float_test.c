#include <stdio.h>

float f1 = 8388608.1;
float f2 = 4194304.25;


const float x = f1 * 3;

int main() {
	int a = 4;
	const int j = a * 3;
	printf("%f %f\n", f1, f2);
	printf("sizeof 23,5F = %ld, sizeof 23,5 = %ld, sizeof 23,5L = %ld\n",
		sizeof 23.5F, sizeof 23.5, sizeof 23.5L);
	printf("sizeof 12.3e-4F = %ld, sizeof 12.3e-4 = %ld, sizeof 12.3e-4L = %ld\n",
		sizeof 12.3e-4F, sizeof 12.3e-4, sizeof 12.3e-4L);

}
