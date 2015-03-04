/* implement the UNIX program tail
 * accept the option -n, where n is the number of tailing lines to output
 */

/* assumptions:
 * the program assumes that it won't run when n is 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUFFER 1024 /* how big can this go? */

char *dupe(const char *);
int getline(char *, int);

int
getline(char *s, int max)
{
	int i, c;
	char *p = s;
	for (i = 0; i < max - 1 && (c = getchar()) !=
		EOF && c != '\n' && c != 0; ++i) {
		*s++ = c;
	}
	if (c == '\n') {
		*s++ = '\n';
	}
		*s = '\0';
	return s - p;
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
		n = n > 0 ? n : -n; /* shouldn't be necessary if atoi() works*/
	}
	if (n == 0) /* skip unnecessary memory allocations */
		return 0;

	char **ring = malloc(sizeof(char *) * n);
	char **p = ring;

	/* intialize storage */
	for (i = 0; i < n; ++i, ++p)
		*p = NULL;
	p = ring;

	/* write lines into ring buffer */
	for (; (getline(line, BUFFER) > 0); ++p) {
		p = (p == &ring[n]) ? ring : p;
		if (*p != NULL)
			free(*p);
		*p = dupe(line);
	}

	/* print lines from ring buffer */
	for (i = 0, p = (p == &ring[n]) ? ring : p;
	     i < n;
	     ++i, ++p) {
		p = (p == &ring[n]) ? ring : p;
		if (*p != NULL)
			fputs(*p, stdout);
	}

	/* free lines */
	for (i = 0; i < n; ++i)
		if (ring[i] != NULL)
			free(ring[i]);
	free(ring);

	return 0;
}
