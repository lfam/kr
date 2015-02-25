#include <stdio.h>
#include <stdlib.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* return month and day from day of year and year */
void month_day(int year, int yearday, int *pmonth, int *pday);
/* return day of year from month & day */
int day_of_year(int year, int month, int day);

void
month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	char *p = NULL;

	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	p = &daytab[leap][1];

	if ((yearday < 1 || yearday > (leap ? 366 : 365)) || (year < 0)) {
		/* bad input */
		*pmonth = 0;
		*pday = 0;
		return;
	}

	for (i = 1; i < 12 && yearday > *p; i++)
		yearday = yearday - *p++;
	*pmonth = i;
	*pday = yearday;
}

int
day_of_year(int year, int month, int day)
{
	int i, leap;
	char *p = NULL;

	leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
	p = &daytab[leap][1];

	/* input validation */
	if (year == 0) {
		fprintf(stderr, "this program won't work for years < 1\n");
	}
	if (year < 0) {
		fprintf(stderr, "negative year, really?\n");
		return 0;
	}
	if (month >= sizeof(daytab) / 2) {
		fprintf(stderr, "too many months!\n");
		return 0;
	}
	if (day < 1 || day > daytab[leap][month]) {
		fprintf(stderr, "how many days in %d-%d?\n", year, month);
		return 0;
	}

	for (i = 1; i < month; i++)
		day = day + *p++;
	return day;
}

int
main(int argc, char **argv)
{
	int exit_status = 0;
	int command;
	int day, nday, month, year;

	if (argc < 2) {
		fprintf(stderr, "you must give a command: 'n' or 'h'\n");
		exit_status = 1;
		goto out;
	}

	command = argv[1][0];
	switch (command) {
	case 'n': /* day_of_year() (n for numeric day) */
		if (argc != 5) {
			fprintf(stderr, "need args: year, month, day\n");
			exit_status = 1;
			goto out;
		}
		year = atoi(argv[2]);
		month = atoi(argv[3]);
		day = atoi(argv[4]);

		if ((nday = day_of_year(year, month, day)) < 1) {
			fprintf(stderr, "day_of_year() failed\n");
			exit_status = 1;
			goto out;
		}
		printf("%d-%d-%d is day %d of %d\n", year, month, day, nday,
		       year);
		break;

	case 'h': /* month_day() (h for human-readable date) */
		month = day = 0;

		if (argc != 4) {
			fprintf(stderr, "need args: year and day of year\n");
			exit_status = 0;
			goto out;
		}
		year = atoi(argv[2]);
		nday = atoi(argv[3]);

		month_day(year, nday, &month, &day);
		if ((!month) || (!day)) {
			fprintf(stderr, "invalid input to month_day()\n");
			exit_status = 1;
			goto out;
		}
		printf("%d-%d-%d for day %d of %d\n", year, month, day, nday,
		       year);
		break;

	default:
		fprintf(stderr, "valid commands are 'n' and 'h'\n");
		exit_status = 1;
		goto out;
	}
		
out:
	return exit_status;
}
