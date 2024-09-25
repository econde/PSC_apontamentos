#include <stdio.h>

short pack_date(int year, int month, int day) {
		return (year - 2000) << (5 + 4) | (month & 0xf) << 5 | (day & 0x1f);
}

void unpack_date(short date, int *year, int *month, int *day) {
	*year = (date >> (5 + 4)) + 2000;
	*month = (date >> 5) & 0xf;
	*day = date & 0x1f;
}

int main() {
	short date = pack_date(1996, 10, 16);
	int y, m, d;
	unpack_date(date, &y, &m, &d);
	printf("%d-%d-%d\n", d, m, y);
}

