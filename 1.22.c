/* Exercise 1-22. Write a program to fold long input lines into two or 
 * more shorter lines after the last non-blank character that occurs 
 * before the n-th column of input. Make sure your program does something 
 * intelligent with very long lines, and if there are no blanks or tabs 
 * before the specified column.
 *
 * line remaining length = 80 
 * count down from 80 as we read through the line
 * get length of each word if we encounter it
 * if word length is greater than remaining length, print newline
 * print word
 *
 * read next char into buffer until ' ', \n, \t, EOF, or \0 and record length
 * decrement from max line length for each character read
 * if remaining is less than word, insert newline, else print word
 * if word length is greater than max, split word every max characters
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int butcher(char *, int, int);

int
butcher(char *word, int len, int max)
{
	int i, j;
	i = j = 0;
	for (; j < len; i++, j++) {
		if ((! (j % max)) && (j != 0)) {
			putchar('\n');
			i = 0;
		}
		putchar(word[j]);
	}
	return(max - i);
}

int
main()
{
	int c;
	char word[1024] = {0};
	int w = 0;
	int max = 5;
	int rem = max;

	while ((c = getchar()) != EOF) {
		if ((word[w] = c) != '\n') w++;

		if (c != ' ' && c != '\n' && c != '\t') {
			continue;
		}
		if (w > max) {
			rem = butcher(word, w, max);
			while (--w > 0) {
				word[w] = '\0';
			}
		} else {
			if (w > rem) {
				putchar('\n');
				rem = max;
			}
			fputs(word, stdout);
			if (c == '\n') {
				rem = max;
			} else {
				rem = rem - w;
			}
			while (--w > 0) {
				word[w] = '\0';
			}
		}
	}
	/* this conditional handles inputs that don't end in \n */
	if (w) {
		fputs(word, stdout);
	}
	return(0);
}
