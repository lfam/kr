#include <stdio.h>
#include <stdlib.h>
#include "lib/libkr.h"

#define MAXLINE 1024
/*
Exercise 3-6. Write a version of itoa that accepts three arguments
instead of two. The third argument is a minimum field width; the
converted number must be padded with blanks on the left if necessary to
make it wide enough.
*/
void itoa(int, char [], unsigned int);

/* itoa:  convert n to characters in s */
void
itoa(int n, char s[], unsigned int w)
{
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {      /* generate digits in reverse order */
		s[i++] = abs(n % 10) + '0';  /* get next digit */
	} while (n /= 10);    /* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	while (i < w)
		s[i++] = ' ';
	reverse(s, i);
}
	
int
main(void)
{
	int n = 1024;
	unsigned int width = 10;
	char out[MAXLINE] = {0};
	itoa(n, out, width); 
	printf("%s\n", out);
	return 0;
}
