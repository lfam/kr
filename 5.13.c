/* implement the UNIX program tail
 * accept the option -n, where n is the number of tailing lines to output
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/libkr.h"
#define BUFFER 1024 /* how big can this go? */

void shift(char **, char **, int);
char *dupe(const char *);

/* shift a pointer array by n */
void
shift(char **p, char **end, int n)
{
	if (*p == *end)
		return;
	*p = *(p + n);
	shift(p + n, end, n);
}

/* duplicate a string */
char *
dupe(const char *s)
{
	if (s == NULL)
		return NULL;

	char *dupe = malloc(strlen(s) + 1);
	if (dupe == NULL)
		return NULL;

	char *p = dupe;
	while ((*p++ = *s++))
		;
	return dupe; 
}

int
main(int argc, char **argv)
{
	char line[BUFFER];
	int i = 0;

	int n = 10;
	if (argc == 2 && *argv[1] == '-') {
		n = atoi(argv[1]);
		n = n > 0 ? n : -n;
	}
	if (n == 0) /* skip unnecessary memory allocations */
		return 0;

	char **lineptrs = malloc(sizeof(char *) * n);
	char **p = lineptrs;
	*p = NULL;

	for (i = 0; i < n; ++i, ++p) /* initialize storage */
		*p = NULL;
	p = lineptrs;

	for (i = 0; i < n; ++i, ++p) /* fill the array */
		if (getline(line, BUFFER) > 0)
			*p = dupe(line);
		else
			break;
	p = lineptrs;

	while (n && getline(line, BUFFER) > 0) { /* cycle the array */
		if (lineptrs[0] != NULL) {
			free(lineptrs[0]);
			lineptrs[0] = NULL;
		}
		shift(lineptrs, &lineptrs[n - 1], 1);
		lineptrs[n - 1] = dupe(line);
	}
	p = lineptrs;

	for (i = 0; i < n && *p != NULL; ++i, ++p)
		fputs(*p, stdout);

	for (i = 0; i < n; ++i)
		if (lineptrs[i] != NULL)
			free(lineptrs[i]);
	free(lineptrs);

	return 0;
}
