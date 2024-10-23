void unpack_date(short date, int *year, int *month, int *day) {
	*year = (date >> 9 & 0b1111111) + 2000;
	*month = date >> 5 & 0b1111;
	*day = date & 0b11111;
}
