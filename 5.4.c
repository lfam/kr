/* Exercise 5-4. Write the function strend(s,t), which returns 1 if the string 
 * t occurs at the end of the string s, and zero otherwise. 
 */

#include <stdio.h>
#include <string.h>
#define TRUE 1

int strend(char *, char *);
int
strend(char *str, char *t)
{
	int tl = strlen(t);
	if (!tl)
		return 0;
	char *tp = t;
	t += tl;
	while (*str) ++str;

	while (*--str == *--t)
		;
	++t;

	return (tp == t) ? 1 : 0;
}

int
main(void)
{
	char s1[] = "this is my big string";
	char s2[] = "ing";
	int result = strend(s1, s2);
	if (result)
		fprintf(stderr, "search term \"%s\" found at end of string!\n", s2);
	return (result) ? 0 : 1;
}
