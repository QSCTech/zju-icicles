#include "stdio.h"

int main(void)
{
	int day, day_year, month, year;
	int looptimes, ri;

	int day_of_year(int year, int month, int day);

	scanf("%d", &looptimes);
	for (ri = 1; ri <= looptimes; ++ri) {
		scanf("%d%d%d", &year, &month, &day);
		day_year = day_of_year(year, month, day);
		printf("days of year: %d\n", day_year);
	}

	return 0;
}

int day_of_year(int year, int month, int day) {
	int day_year = 0, i;
	for (i = 1; i < month; ++i) {
		switch (i) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			day_year += 31;
			break;
		case 4: case 6: case 9: case 11:
			day_year += 30;
			break;
		case 2:
			if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
				day_year += 29;
			} else {
				day_year += 28;
			}
			break;
		}
	}
	day_year += day;
	return day_year;
}
