int a;
static int b;
int x = 20;
static int y = 24;
int array[5];
int table[] = {1, 2, 3, 4, 5};
char matrix[100][20];
char n[] = "Manuel";
const char m[] = "Joaquim";
const char *d = "Augusto";
const char *const f = "Ezequiel";

#define ARRAY_SIZE(a) (sizeof(a) / sizeof (a)[0])

void func() {
	int j;
	int k = 34;
	register int l;
	const int m = 20;
	static const int n = 20;
	static int o = 55;
	extern int a;
	auto int q;

	l = 3;
	o++;
	a = o;
	q = m;
	j = l;
}

int main() {
//	func();
//	func();
	*c = 'a';
	*m = 's';
//	*d = 'a';
//	*e = 'a';
//	*f = 'a';
}
