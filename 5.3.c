#include <stdio.h>
#include <stdlib.h>
#define strcat strcat_original
#include <string.h>
#undef strcat

char *strcat(char *dest, const char *str);

char *
strcat(char *dest, const char *str)
{
	char *ret = dest;

	while (*dest) {
		++dest;
	}
	while ((*dest = *str)) {
		dest++; str++;
	}
	*dest = '\0';

	return ret;
}

int
main(void)
{
/*
	char s1[] = {47, 48, 49, 50, 51};
	char s2[] = {46, 56, 45, 0};
*/
	char s1[] = {0};
	char s2[] = {0};
	printf("%s\n", strcat(s1, s2));

	return 0;
}
