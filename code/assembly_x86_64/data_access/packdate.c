short pack_date(int year, int month, int day) {
	short date = day;
	date = date + (month << 5);
	date = date + ((year - 2000) << 9);
	return date;
}
