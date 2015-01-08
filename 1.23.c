#include <stdio.h>
#include <stdlib.h>
/*
 * This is a program to remove comments from C programs. It will handle both
 * c89 and c99 style comments.
 *
 * c99 style (slash slash):
 * if (slash slash), getchar() until newline, putchar() newline.
 * if (c == '\n') break;
 *
 * c89 style (slash asterisk):
 * if slash, then if asterisk
 * getchar() until asterisk, then if slash, else repeat
 * this is the first place where we call getchar() inside the main loop
 * 
 * It must handle quoted strings and literals correctly. This means not
 * looking for comments between "s and 's.
 *
 * Finally, it should handle escaped characters. This means \. If we encounter
 * a \, and we are not in a comment, pass it and next character. This may be
 * the second place where we want to call getchar() within the main getchar()
 * loop.
 *
 * The question is, how do we put these requirements together in order to make
 * the program work correctly?
 */


#define IN 1
#define OUT 0

void die(int);
void
die(int status)
{
	exit(status);
}

int
main()
{
	/*
	 * The four special states we can be in. 
	 *
	 * Luckily, these states are exclusive. Meaning, if we are in a quote,
	 * we cannot be in a constant or comment, and the same for the other
	 * three states.
	 */
	int quote = 0;
	int constant = 0;
	int comment89 = 0;
	int comment99 = 0;
	int i = 0;

	int c;
// Let's try only calling getchar() here...
	while ((c = getchar()) != EOF) {
		i++;
//		fprintf(stdout, "%d\n", i);

		if (i == 2476 || i == 2477 || i == 2478) {
			fprintf(stderr, "i = %d\n", i);
			fprintf(stderr, "%d quote\n", quote);
			fprintf(stderr, "%d constant\n", constant);
			fprintf(stderr, "%d comment89\n", comment89);
			fprintf(stderr, "%d comment99\n", comment99);
			fprintf(stderr, "\n");
		}
		if (quote) {
			putchar(c);
			if (c == '"') quote = OUT;
			continue;
		}
		if (constant) {
			putchar(c);
			if (c == 39) constant = OUT;
			continue;
		}
		if (comment89) {
			if (c == '*') {
				if ((c = getchar()) == '/') {
					comment89 = OUT;
				}
			}
			continue;
		}
		if (comment99) {
			if (c == '\n') comment99 = OUT;
			continue;
		}

		if (c == '\\') {
			putchar(c);
			c = getchar();
			putchar(c);
			continue;
		} else if (c == '/') {
			int buf = c;
			c = getchar();
			if (c == '*') {
				comment89 = IN;
			} else if (c == '/') {
				comment99 = IN;
			} else {
				putchar(buf);
				putchar(c);
			}
			continue;
		} else if (c == '"') {
			quote = IN;
			putchar(c);
			continue;
		} else if (c == 39) {
			constant = IN;
			putchar(c);
			continue;
		}
		putchar(c);
/*y
		if quote
			echo
			if c == \"
				quote = OUT
			continue

		if constant
			echo
			if c == \'
				constant = OUT
			continue		

		if comment89
			if c == *
				getchar
				if c == /
					comment89 = OUT
			continue

		if comment99
			if c == \n
				comment99 = OUT
			continue

	Done with state checking, into normal mode 
		if c == \\
			putchar
			getchar
			putchar
			continue
		if c == /
			buf = /
			getchar
			if c == *
				comment89 = IN
			else if c == /
				comment99 = IN
			else
				put buf
				putchar
			continue
		if c == \"
			quote = IN
			putchar
			continue
		if c == '
			constant = IN
			putchar
			continue
*/
	}

	return 0;
}
