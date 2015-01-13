/*
 * K&R exercise 1.24
 * Rudimentary C syntax checker.
 * TODO:
 * unbalanced parentheses
 * unbalanced brackets
 * unbalanced braces
 * single quotes
 * double quotes
 * escape sequences
 * comments
 */
#include <stdio.h>

#define IN 1
#define OUT 0

/* Exit codes */
#define BAD_ESCAPE_SEQUENCE 2

int escape_check(int);

int
escape_check(int c)
{
	int ret = 0;
	int i = 0;

	switch (c) {
	case 'a':
	case 'b':
	case 'f':
	case 'n':
	case 'r':
	case 't':
	case 'v':
	case '\\':
	case '?':
	case 39 :
	case '"':
		ret = 1;
		break;
	case 'x':
		/* hex checker, upper and lower-case */
		;
		i = 0;
		while ((c = getchar() != EOF) && i < 2) {
			putchar(c);
			if ((((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F')) || (c >= 'a') && (c <= 'f'))) {
				i++;
			} else {
				break;
			}
		}
		if (i == 2) ret = 1;
		break;
	default:
		/* octal checker */
		;
		i = 0;
		while ((c = getchar() != EOF) && i < 3) {
			putchar(c);
			if ((c >= '0') && (c <= '7')) {
				i++;
			} else {
				break;
			}
		}
		if (i == 3) ret = 1;
		break;
	}
	return ret;
}

int
main()
{
	int exit_status = 0;	
	int line_no = 0;

	int quote = OUT;
	int constant = OUT;
	int comment89 = OUT;
	int comment99 = OUT;
	int curly = 0;
	int paren = 0;
	int subscript = 0;

	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\n') line_no++;
		if (quote) {
			putchar(c);
			if (c == '"') quote = OUT;
			continue;
		}
		if (constant) {
			putchar(c);
			if (c == 39) constant = OUT;
		}
		if (comment89) {
			putchar(c);
			if (c == '*') {
				if ((c = getchar()) == '/') {
					comment89 = OUT;
				}
			}
			putchar(c);
			continue;
		}
		if (comment99) {
			putchar(c);
			if (c == '\n') comment99 = OUT;
			continue;
		}

		switch (c) {
		case '\\':
			putchar(c);
			c = getchar();
			if (! escape_check(c)) {
				exit_status = BAD_ESCAPE_SEQUENCE;
				goto out;
			}
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

	}

out:
	if (exit_status != 0) {
		fprintf(stderr, "error on line %d\n", line_no);
		fprintf(stderr, "quote: %d\n", quote);
		fprintf(stderr, "constant: %d\n", constant);
		fprintf(stderr, "c89 comment: %d\n", comment89);
		fprintf(stderr, "curly: %d\n", curly);
		fprintf(stderr, "parentheses: %d\n", paren);
		fprintf(stderr, "subscript: %d\n", subscript);
	}
	if (c != '\n') putchar('\n');
	return exit_status;
}
