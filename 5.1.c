/* Exercise 5-1. As written, getint treats a + or - not followed by a digit as
 * a valid representation of zero. Fix it to push such a character back on the 
 * input. 
 *
 * Each call sets array[n] to the next integer found in the input and increments
 * n. Notice that it is essential to pass the address of array[n] to getint.
 * Otherwise there is no way for getint to communicate the converted integer
 * back to the caller.
 *
 * Our version of getint returns EOF for end of file, zero if the next input is
 * not a number, and a positive value if the input contains a valid number. 
 */

#include <stdio.h>
#include <ctype.h>
#include "lib/libkr.h"
#define SIZE 10

int getint(int *);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;
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
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');

	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int
main(void)
{
	int array[SIZE];
	if ((getint(&array[0]) > 0))
		printf("%d\n", array[0]);
	return 0;
}
