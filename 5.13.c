/* implement the UNIX program tail
 * accept the option -n, where n is the number of tailing lines to output
 */

/* assumptions:
 * the program assumes that it won't run when n is 0
 */

#include <stdio.h>
#include <stdlib.h>
#include "lib/libkr.h"

#define BUFFER 1024 /* how big can this go? */

char *dupe(const char *, int);

/* duplicate a string */
char *
dupe(const char *s, int len)
{
	if (s == NULL)
		return NULL;

	char *dupe = malloc(len + 1);
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
		n = -n;
	}
	if (n == 0) /* nothing to do */
		return 0;

	char **ring = malloc(sizeof(char *) * n);
	char **p = ring;
	char **end = &ring[n];

	/* intialize storage */
	while (p != end)
		*(p)++ = NULL;
	p = ring;

	/* write lines into ring buffer */
	int len = 0;
	for (;
	     (len = getline(line, BUFFER)) > 0;
	     (p + 1 == end) ? p = ring : ++p) {
		if (*p != NULL)
			free(*p);
		*p = dupe(line, len);
	}
	/* print lines from ring buffer */
/* this needs i for when n == 1 ? 
 * when n == 1, start == end... no! end is past the end of the array!
 */
	for (i = 0; i < n; ++i, (p + 1 == end) ? p = ring : ++p)
		if (*p != NULL)
			fputs(*p, stdout);

	/* free lines */
	while (ring != end)
		if (*ring != NULL)
			free(*(ring)++);
	free(ring - n);

	return 0;
}
