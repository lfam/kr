#include <stdio.h>
/* 2.10
 * Rewrite the funciton lower, which converts upper case letters to lower case,
 * using a conditional expression instead of if-else.
int
lower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
}
*/

int
lower(int c)
{
	return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : (c);
}

int
main(void)
{
	int c = 0;
	while ((c = getchar()) != EOF) {
		if (c != '\n') printf("%c\n", lower(c));
	}
	return 0;
}
