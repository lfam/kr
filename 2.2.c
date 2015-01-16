#include <stdio.h>

#define LIM 1024

int
main()
{
	int i;
	char s[LIM];

	int c;
	while (i < LIM - 1) {
		c = getchar();
		if (c == '\n') break;
		if (c == EOF) break;
		s[i++] = c;
	
	}
	s[i++] = '\n';
	s[i++] = '\0';

	fputs(s, stdout);

	return 0;
}
