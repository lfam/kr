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
#include <stdio.h>

#define IN 1
#define OUT 0

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
	int quote = OUT;
	int constant = OUT;
	int comment89 = OUT;
	int comment99 = OUT;

	int c;
// Let's try only calling getchar() here...
	while ((c = getchar()) != EOF) {
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

		switch (c) {
		case '\\':
			putchar(c);
			c = getchar();
			putchar(c);
			continue;
		case '/':
			;
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
		case '"':
			quote = IN;
			putchar(c);
			continue;
		case 39:
			constant = IN;
			putchar(c);
			continue;
		default: break;
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
