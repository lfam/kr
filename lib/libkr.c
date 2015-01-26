#include <stdio.h>
#include "libkr.h"

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

/* reverse:  reverse string s in place */
void reverse(char s[], int len)
{
	int c, i, j;

	for (i = 0, j = len - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
