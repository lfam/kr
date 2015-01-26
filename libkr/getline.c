#include <stdio.h>

int
getline(char s[], int max) {
	int i, c;
	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}
