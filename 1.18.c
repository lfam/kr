/*
 * http://clc-wiki.net/wiki/K%26R2_solutions:Chapter_1:Exercise_18
 */

#include <stdio.h>

#define MAXLINE 1000

/* delete trailing blanks, tabs, and blank lines */

int
getline(char s[], int max);

int
main(void)
{
	int len, i;
	char line[MAXLINE], longest[MAXLINE];

	while ((len = getline(line, MAXLINE)) != 0) {
		if (len > 1) {
			i = len - 1;
			while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
				--i;
			}
			line[++i] = '\n';
			line[++i] = '\0';
			printf("%s", line);
		}
	}

	return 0;
}

int
getline(char s[], int max) {
	int i, c;
	for (i=0; i<max-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}
