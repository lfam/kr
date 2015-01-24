#include <stdio.h>

int butcher(char *, int, int);
/* butcher()
 * This is for words that are longer than the max line length. We fill out the
 * remaining space on the line, and then print the rest of the word, inserting
 * a newline if we are at line max.
 *
 * Takes a char *, its length, the remaining space on current line, and the max line
 * length. returns remaining space on line (ie, int rem);
 *
 * count down rem to 0, then print newline and rem = max
 */
int
butcher(char *word, int rem, int max)
{
	int j = 0;
	while (word[j] != '\0') {
		if (rem-- > 0) {
			putchar(word[j++]);
		} else {
			putchar('\n');
			rem = max;
		}
	}
	return(rem + 1);
}

int
main(void)
{
	int w = 0;
	char word[1024] = {0};
	int max = 5;
	int rem = max;
	while ((word[w++] = getchar()) != EOF) {
		if (word[w - 1] == '\n') {
			int left = butcher(word, rem, max);
			printf("%d chars left\n", left);
			while (--w > 0) {
				word[w] = '\0';
			}
			rem = max;
		}
	}
	return 0;
}
