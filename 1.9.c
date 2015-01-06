#include <stdio.h>

#define BLANK 1
#define NOTBLANK 0

int
main(void)
{
	int c;
	int state;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			state = BLANK;
		} else if (state == BLANK ) {
			state = NOTBLANK;
			printf(" ");
			putchar(c);
		} else {
			putchar(c);
		}
	}
	return(0);
}
