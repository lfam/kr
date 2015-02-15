/*
       As with strcat(), the resulting string in dest is always 
null-terminated.

       If  src contains n or more bytes, strncat() writes n+1 bytes to dest 
(n from src plus
       the  terminating  null  byte).   Therefore,  the  size  of  dest  must 
 be  at  least
       strlen(dest)+n+1.
*/
#include <stdio.h>
#define strncat strncat_original
#include <string.h>
#undef strncat

char *strncat(char *, const char *, size_t);
char *strncpy(char *, const char *, size_t);
int strncmp(const char *, const char *, size_t);

char *
strncat(char *dest, const char *src, size_t n)
{
	char *ret = dest;

	while (*dest)
		++dest;
	while ((n--) && (*dest++ = *src++))
		;
	*dest = '\0';

	return ret;
}

char *
strncpy(char *dest, const char *src, size_t n)
{
	char *ret = dest;
	size_t i;

	for (i = 0; i < n && src[i]; i++)
		dest[i] = src[i];
	for (; i < n; i++)
		dest[i] = '\0';
	

	return ret;
}

int
strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i, j, x;
	i = j = x = 0;

	for (x = 0; x < n && (s1[i] == s2[j]) && s1[i] && s2[j]; ++i, ++j, ++x)
		;
	for (; i < n && s1[i]; ++i)
		;
	for (; i < n && s2[j]; ++j)
		;

	return (int)(i - j);
}

int
main(void)
{
	char s1[] = {47, 48, 49, 50, 51, 0};
	printf("s1[]: %s\n", s1);
	char s2[] = "456789";
	printf("s2[]: %s\n", s2);

	printf("strncat:\n");
	printf("%s\n", strncat(s1, s2, 0));

	char s3[] = {47, 48, 49, 50, 51, 0};
	char s4[] = "456789";
	printf("strncpy:\n");
	printf("%s\n", strncpy(s3, s4, 0));


	char s5[] = "";
	char s6[] = "111";
	printf("strncmp:\n");
	printf("%d\n", strncmp(s5, s6, 3));
	return 0;
}
