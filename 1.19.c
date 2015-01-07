#include <stdio.h>
#include <stdlib.h>

void reverse(char *, ssize_t);

void
reverse(char *line, ssize_t len)
{
	int i = 0;
	int j = len - 2;
	char *rline = NULL;
	rline = malloc(len);

	while (i < len - 1) {
		rline[i] = line[j];
		i++;
		j--;
	}
	puts(rline);
}

int
main()
{
	char *line = NULL;
	ssize_t len = 0;
	size_t buf_len = 0;

	len = getline(&line, &buf_len, stdin);

	fputs(line, stdout);
	reverse(line, len);

	return(0);
}
