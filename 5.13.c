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

/* duplicate a stringbuf */
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

	int n = 10;
	if (argc == 2 && *argv[1] == '-')
		n = -(atoi(argv[1]));
	if (n < 1) /* nothing to do */
		return 0;

	char **ringbuf = malloc(sizeof(char *) * n);
	if (ringbuf == NULL) {
		fputs("ERROR: out of memory\n", stderr);
		return 1;
	}
	char **p = ringbuf;
	char **end = &ringbuf[n];

	/* intialize storage */
	while (p != end)
		*(p)++ = NULL;
	p = ringbuf;

	/* write lines into ring buffer */
	int len = 0;
	while ((len = getline(line, BUFFER)) > 0) {
		free(*p);
		*p = dupe(line, len);
		(p + 1 == end) ? p = ringbuf : ++p;
	}

	/* print lines from ringbuf buffer */
	while (n--) {
		if (*p != NULL)
			fputs(*p, stdout);
		(p + 1 == end) ? p = ringbuf : ++p;
	}
	p = ringbuf;

	/* free lines */
	while (p != end)
		free(*(p)++);
	free(ringbuf);

	return 0;
}
