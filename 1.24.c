/*
 * K&R exercise 1.24
 * Rudimentary C syntax checker
 *
 * WORKS:
 * escape sequences
 *
 * TODO:
 * Don't use continue wantonly in input loop
 * unbalanced parentheses
 * unbalanced brackets
 * unbalanced braces
 * single strings
 * double strings
 * comments
 */
#include <stdio.h>

#define IN 1
#define OUT 0

/* Exit codes */
#define BAD_ESCAPE_SEQUENCE 2
#define UNBALANCED_PARENTHESES 3
#define UNBALANCED_BRACKETS 4
#define UNBALANCED_BRACES 5
#define TRUNCATION 6
#define CHAR_LITERAL_UNTERMINATED 7
#define COMMENT_UNTERMINATED 8
#define STRING_UNTERMINATED 9

int escape_check(int);

int
escape_check(int c)
{
	int ret = 0;
	int i = 0;
	int j = 0;

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
	case 'x':;
		/* hex checker, upper and lower-case */
		while ((i < 2 && (c = getchar()) != EOF)) {
			putchar(c);
			j++;
			if (
				(((c >= '0') && (c <= '9')) || 
				((c >= 'A') && (c <= 'F')) || 
				((c >= 'a') && (c <= 'f'))))
			{
				i++;
			} else {
				break;
			}
		if (i == 2) ret = 1;
		}
		break;
	default:;
		/* octal checker */
		if (! ((c >= '0') && (c <= '7'))) break;
		while (i < 2 && ((c = getchar()) != EOF)) {
			putchar(c);
			j++;
			if ((c >= '0') && (c <= '7')) {
				i++;
			} else {
				break;
			}
		}
		if (i == 2) ret = 1;
		break;
	}
	return ret;
}

int
main()
{
	int err = 0;

	int brace = 0;
	int bracket = 0;
	int char_literal = OUT;
	int comment_maybe = OUT;
	int comment89 = OUT;
	int comment99 = OUT;
	int paren = 0;
	int string = OUT;

	int since_newline = 0;
	int lines = 1;
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			since_newline = 0;
			lines++;
		} else {
			since_newline++;
		}

		/* Take action based on special states we can be in */
		if (string) {
			/*
			 * in a string literal, we only need to check for '"',
			 * which ends the literal
			 */
			putchar(c);
			if (c == '"') string = OUT;
			continue;
		} else if (char_literal) {
			/*
			 * in a character literal, 3 things can happen:
			 * 1) we get a 39, ending the literal
			 * 2) we get a \, entering an escape sequence
			 * 3) we get anything else, and remain in the literal
			 */
			putchar(c);
			if (c == 39) {
				char_literal = OUT;
			} else if (c == '\\') {
				c = getchar();
				putchar(c);
				if (! escape_check(c)) {
					err = BAD_ESCAPE_SEQUENCE;
					goto out;
				}
			}
			continue;
		} else if (comment_maybe) {
			/*
			 * This state is the result of reading a '/' while not
			 * in any other special state. Now, we find out if we
			 * are entering a comment, and if so, what kind.
			 */
			putchar(c);
			if (c == '*') {
				comment89 = IN;
			} else if (c == '/') {
				comment99 = IN;
			}
			comment_maybe = OUT;
			continue;
		} else if (comment89) {
			/*
			 * in a c89 comment, x things can happen:
			 * 1) we get a *. then we must check for /, which ends the comment
			 * 2) we get anything else, continuing the comment
			 */
			putchar(c);
			if (c == '*') {
				if ((c = getchar()) == '/') {
					putchar(c);
					comment89 = OUT;
				} else {
					/* undo side effect of previous block */
					ungetc(c, stdin);
				}
			}
			continue;
		} else if (comment99) {
			/*
			* there is no syntax to check in a c99 comment, except
			 * for '\n', which is the end of the comment
			 */
			putchar(c);
			if (c == '\n') comment99 = OUT;
			continue;
		}

		/*
		 * If we are not in a special state, we get here.
		 * These conditions are in ASCII order.
		 */
		switch (c) {
		case '"':
			string = IN;
			break;
		case 39:
			char_literal = IN;
			break;
		case '(':
			paren++;
			break;
		case ')':
			paren--;
			break;
		case '/':;
			comment_maybe = IN;
			break;
		case '[':
			bracket++;
			break;
		case '\\':
			putchar(c);
			c = getchar();
			if (! escape_check(c)) {
				err = BAD_ESCAPE_SEQUENCE;
				goto out;
			}
			break;
		case ']':
			bracket--;
			break;
		case '{':
			brace++;
			break;
		case '}':
			brace--;
			break;
		default: break;
		}
		putchar(c);
	}

	/* Done reading input */
	if (since_newline > 0) {
		c = putchar('\n');
		err = TRUNCATION;
		goto out;
	}
	if (brace != 0) {
		err = UNBALANCED_BRACES;
		goto out;
	} else if (bracket != 0) {
		err = UNBALANCED_BRACKETS;
		goto out;
	} else if (char_literal != OUT) {
		err = CHAR_LITERAL_UNTERMINATED;
		goto out;
	} else if (comment_maybe != OUT && comment89 != OUT && comment99 != OUT) {
		err = COMMENT_UNTERMINATED;
		goto out;
	} else if (paren != 0) {
		err = UNBALANCED_PARENTHESES;
		goto out;
	} else if (string != OUT) {
		err = STRING_UNTERMINATED;
		goto out;
	}
out:
	if (err != 0) {
		/*
		 * Line number doesn't work... at least you know the
		 * error took place before the reported line.
		 */
		fprintf(stderr, "error on line %d\n", lines);
		fprintf(stderr, "string: %d\n", string);
		fprintf(stderr, "character literal: %d\n", char_literal);
		fprintf(stderr, "c89 comment: %d\n", comment89);
		fprintf(stderr, "brace: %d\n", brace);
		fprintf(stderr, "parentheses: %d\n", paren);
		fprintf(stderr, "bracket: %d\n", bracket);
	}
	if (c != '\n') putchar('\n');
	return err;
}
