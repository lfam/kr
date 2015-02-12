#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void recur_itoa(int, char *);
void reverse(char *, int, int);

void
reverse(char *s, int i, int j)
{
	if (i < j) {
		int buf = s[i];
		s[i] = s[j];
		s[j] = buf;
		reverse(s, ++i, --j);
	}
}

void
recur_itoa(int n, char *s)
{
	if (n / 10) {
		recur_itoa(n / 10, s + 1);
	}
	*s = (n % 10 + '0');
}
	
int
main(void)
{
	int d = -3567;

	char *line = calloc(1024, sizeof(char));
	char *s = line;

	if (d < 0) {
		*s++ = '-';
		d = -d;
	}
	char *rev = s;

	recur_itoa(d, s);
	reverse(rev, 0, strlen(rev) - 1);

	printf("line %s\n", line);
	free(line);

	return 0;
}
