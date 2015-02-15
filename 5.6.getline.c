#include <stdio.h>
#include <stdlib.h>

int
getline(char *s, int max) {
	int i, c;
	char *p = s;
	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n' && c != 0; ++i) {
		*s++ = c;
	}
	if (c == '\n') {
		*s++ = '\n';
	}
	*s = '\0';
	return s - p;
}

int
main(void)
{
	int max = 1024;
	char line[max];
	int len = 0;
	while ((len = getline(line, max)) > 0) { 
		printf("len %d\n------\n", len);
		char *p = line;
		while (*p)
			printf("%d\n", *p++);
		putchar(10);
	}
	return 0;
}
