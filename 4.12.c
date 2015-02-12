#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/binary_print.h"
/* itoa:  convert n to characters in s */
void itoa(int, char []);
void reverse(char *, int, int);

void
reverse(char *s, int i, int j)
{
	if (i < j) {
		int buf = s[i];
		s[i] = s[j];
		s[j] = buf;
		reverse(s, ++i, --j);
	}
}

void
itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {      /* generate digits in reverse order */
		s[i++] = abs(n % 10) + '0';  /* get next digit */
		fprintf(stderr, "%c\n", s[i - 1]);
	} while (n /= 10);    /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
}
	
int
main(void)
{
	char line[1024];
	int d = 4567;
	itoa(d, line);
	printf("%s\n", line);
	return 0;
}
