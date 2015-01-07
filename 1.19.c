#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

void reverse(char [], int);
int getline(char [], int);

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

void
reverse(char line[], int len)
{
	int i = 0;
	int j = len - 1;

	while (i <= len - 1) {
		putchar(line[j]);
		i++;
		j--;
	}
	putchar('\n');
}

int
main()
{
	char line[MAXLINE];
	int len;

	while ((len = getline(line, MAXLINE)) > 0) {
		fputs(line, stdout);

		if (line[len - 1] != '\n') {
			putchar('\n');
		} else {
			len--;
		}
		reverse(line, len);
	}
	return(0);
}
