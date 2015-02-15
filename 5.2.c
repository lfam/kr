#include <stdio.h>
#include <ctype.h>
#include "lib/libkr.h"
#define SIZE 10

int getfloat(double *);

/* getfloat: get next double from input into *pn */
int getfloat(double *pn)
{
	int c, sign;
	double power;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '-' || c == '+') {
		int buf = c;
		if (!isdigit(c = getch())) {
			ungetch(c);
			ungetch(buf);
			return 0;
		}
	}
	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');
	if (c == '.') 
		c = getch();
	if (!isdigit(c)) {
			ungetch(c);
			ungetch('.');
			goto out;
	}
	for (power = 1.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
		power *= 10;
	}

	*pn = (*pn * sign) / power;
	if (c != EOF)
		ungetch(c);
out:
	return c;
}

int
main(void)
{
	double array[SIZE];
	if ((getfloat(&array[0]) > 0))
		printf("%g\n", array[0]);
	return 0;
}
