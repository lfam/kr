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

int break_word(char *, int, int);

int
break_word(char *word, int w, int max)
{
	int j;
	for (j = 0; j <= w; j++) {
		if ((! (j % max)) && (j != 0)) {
			putchar(10);
		}
		putchar(word[j]);
		fflush(stdout);
	}
	return(w % max);
}

int
main()
{
	int c;
	char word[1024] = {0};
	int w = 0;
	int max = 6;
	int rem = max;

	fprintf(stdout, "012345\n");

	while ((c = getchar()) != EOF) {
		word[w] = c;
		w++;

		fprintf(stderr, "\n-->%d\t", w);
		fprintf(stderr, "%d-->", rem);

		if (c != ' ' && c != '\n' && c != '\t') {
			continue;
		}
		if (w > max) {
			fprintf(stderr, "MAX\n");
			rem = break_word(word, w, max);
			w = 0;
			memset(word, 0, sizeof(word));
			continue;
		}

		if (w > rem) {
			fprintf(stderr, "NO REM");
			putchar('\n');
			fflush(stdout);
			rem = max;
		}
		fputs(word, stdout);
		fflush(stdout);
		c != '\n' ? (rem = rem - w) : (rem = max);
		while (--w > 0) {
			word[w] = '\0';
		}
	}
	return(0);
}
