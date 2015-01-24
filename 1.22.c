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
 */
 
#include <stdio.h>
#include <string.h>

int butcher(char *, int, int);
int reset(char *, unsigned int);
/*
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
		/* don't start a line with ' ' */
		if ((rem == max) && (word[j] == ' ')) {
			++j;
		} else if (rem-- > 0) {
			putchar(word[j++]);
		} else {
			putchar('\n');
			rem = max;
		}
	}
	return(rem + 1);
}

/* basically memset to null, return index into char array */
int
reset(char *word, unsigned int len)
{
	while (len > 0) {
		word[--len] = '\0';
	}
	return len;
}

int
main(void)
{
	int c;
	char word[1024] = {0};
	unsigned int w = 0;
	int max = 72;
	int rem = max;


	while ((c = getchar()) != EOF) {
		/* this could go at end of block in an else but it's nicer up here */
		((word[w] = c) == '\n') || w++;

		/* read until word is over... */
		if (c == ' ' || c == '\n' || c == '\t') {
			/* if word is longer than max line, cut it up */
			if (w > max) {
				rem = butcher(word, rem, max);
				w = reset(word, w);
			} else {
				/* if word won't fit in rest of line, start on
				 * a new line
				 */
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
				w = reset(word, w);
			}
		}
	}
	/* this prints inputs that don't end in \n. it does NOT add the \n */
	if (w) {
		fputs(word, stdout);
	}
	return(0);
}
