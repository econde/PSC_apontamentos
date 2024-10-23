
void unpack_date(short, int *, int *, int *);

int main() {
	int year;
	int month;
	int day;
	short adate = 2024 - 2000 << 9 | 10 << 5 | 8;
	unpack_date(adate, &year, &month, &day);
}
