#include <stdio.h>

int any(char [], char []);

int
any(char s1[], char s2[])
{
	int i, k;

	i = k = 0;
	for (i = k = 0; s1[i] != '\0'; k = 0, i++) {
		for (k = 0; s2[k] != '\0'; k++) {
			if (s1[i] == s2[k]) goto out;
		}
	}
	i = -1;
out:
	return i;
}

int
main(void)
{
	char s1[] = "Hello";
	char s2[] = "yx";
	
	printf("%d\n", any(s1, s2));
	return 0;
}
