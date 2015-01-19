#include <stdio.h>

void ssqueeze(char [], char[]);

/* ssqueeze: delete all chars in s2 from s1 */
void
ssqueeze(char s1[], char s2[])
{
   	int i, j, k, l;

  	k = 0;
   	while (s2[k] != '\0') {
		k++;
	}
	l = k;

   	i = j = k = 0;
	while (s1[i] != '\0') {
		while (s2[k] != '\0') {
			if (s1[i] == s2[k]) break;
			k++;
		}
		if (k == l) {
			s1[j] = s1[i];
			j++;
		}
		i++;
		k = 0;
	}
	s1[j] = '\0';
}

int
main(void)
{
	char s1[] = "Hello";
	char s2[] = "Hoe";

	ssqueeze(s1, s2);

	printf("%s\n", s1);
	return 0;
}
