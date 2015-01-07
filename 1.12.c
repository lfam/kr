#include <stdio.h>
#include <string.h>

#define TAB 9
#define NEWLINE 10
#define BLANK 32

int
main()
{
	char word[1024] = {0};
	int w = 0;
	int c;

	while ((c = getchar()) != EOF) {
		word[w] = c;
		w++;

		if ((c == TAB) || (c == NEWLINE) || (c == BLANK)) {
			fputs(word, stdout);
			if (word[w - 1] != NEWLINE)
				putchar(10);
			memset(word, 0, sizeof(word));
			w = 0;
		}
	}
	return(0);
}
