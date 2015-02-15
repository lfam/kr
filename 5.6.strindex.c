#include <stdio.h>
#include "lib/libkr.h"

#define MAXLINE 1024

int strindex(char *, char *);

int
strindex(char *str, char *pat)
{
	char *anchor = str;
	char *pstr = NULL;
	char *ppat = NULL;

	for (; *str; ++str) {
		pstr = str;
		ppat = pat;
		for (; *pstr == *ppat; ++pstr, ++ppat)
			;
		if (*ppat == '\0')
			return str - anchor;
	}
	return -1;
}

int
main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "give a search term as the first argument\n");
		return 1;
	}
	char *pattern= &argv[1][0];
	char line[MAXLINE];
	int len = 0;
	int i = 0;

	while ((len = getline(line, MAXLINE - 1)) > 0) {
		if ((i = strindex(line, pattern)) >= 0)
			printf("%d\n", i);
		else
			printf("pattern not found\n");
	}
	return 0;
}
