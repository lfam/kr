#include <stdio.h>

#define TAB 9
#define NEWLINE 10
#define BLANK 32

int
main()
{
	int nn = 0;
	int nb = 0;
	int nt = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == TAB) nt++;
		if (c == BLANK) nb++;
		if (c == NEWLINE) nn++;
	}

	printf("%d newlines\n", nn);
	printf("%d blanks\n", nb);
	printf("%d tabs\n", nt);
}
