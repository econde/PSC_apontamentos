#include "add.h"

extern int a, b;
static const int x = X;
int y = 33;
static int *pa = &a;
static int *pb;
int res;

static int multiply(int a, int b) {
	return a * b;
}

int calculate() {
	pb = &b;
	res = *pa + *pb + multiply(x, y);
	return res;
}
