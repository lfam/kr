#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "../lib/binary_print.h"
void itob(int, char [], unsigned int);
void reverse(char [], int);

/* itob:  convert n to characters in s, according to radix b */
void
itob(int n, char s[], unsigned int b)
{
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {      /* generate digits in reverse order */
		s[i++] = abs(n % b) + '0';  /* get next digit */
		fprintf(stderr, "%c\n", s[i - 1]);
	} while (n /= b);    /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s, i);
}
	
void
reverse(char line[], int len)
{
	int i = 0;
	int j = len - 1;

	while (i <= len - 1) {
		putchar(line[j]);
		i++;
		j--;
	}
	putchar('\n');
}

int
main(void)
{
	char line[1024];
	fprintf(stderr, PRINTF_BYTE32"\n", BYTE32(127));
	fprintf(stderr, PRINTF_BYTE32"\n", BYTE32(-128));
	fprintf(stderr, PRINTF_BYTE32"\n", BYTE32(INT_MIN));
	itob(1024, line, 16);
	fprintf(stderr, PRINTF_BYTE32"\n", BYTE32((INT_MIN + 1)));
	return 0;
}

