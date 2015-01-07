#include <stdio.h>

#define BACK 8
#define TAB 9
#define BSLASH 92

int
main()
{
	int c;
	while ((c = getchar()) != EOF) {
		if (c == BACK) {
			putchar(92);
			putchar('b');
		} else if (c == TAB) {
			putchar(92);
			putchar('t');
		} else if (c == BSLASH) {
			putchar(92);
			putchar(92);
		} else {
			putchar(c);
		}
	}

	return(0);
}
