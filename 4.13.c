#include <stdio.h>
#define reverse reverse_libkr
#include "lib/libkr.h"
#undef reverse

void reverse(char *, int, int);

void
reverse(char *s, int i, int j)
{
	if (i <= j) {
		int buf = s[i];
		s[i] = s[j];
		s[j] = buf;
		reverse(s, ++i, --j);
	}
}

int
main(void)
{
	int len = 0;
	char line[1024] = {0};

	while ((len = getline(line, 1023)) > 0) {
		line[len - 1] = '\0';
		reverse(line, 0, len - 2);
		printf("%s\n", line);
	}

	return 0;
}
