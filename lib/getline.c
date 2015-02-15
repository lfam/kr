#include <stdio.h>

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
