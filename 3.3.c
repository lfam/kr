#include <stdio.h>
#include <ctype.h>
#define MAXLINE 1024 
/* 3.3
 * Write a function expand(s1, s2) that expands shorthand notations like a-z in
 * the string s1 into the equivalent complete list abc...xyz in s2. Allow for
 * letters of either case and digits, and be prepared to handle cases like
 * a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken
 * literally.
 */
int expand(char [], char []);

int
expand(char s1[], char s2[])
{
	int status = 1;

	char head, tail;
	int hyphen; /* flag for trailing hyphen */
	int i, j;
	i = j = head = tail = hyphen = 0;

	/* process leading hyphen manually */
	if (s1[0] == '-') {
		i++;
		s2[0] = '-';
		j++;
	}

	for (; s1[i] != '\0'; i++) {
		if (! isalnum(s1[i]) && s1[i] != '-') {
			fprintf(stderr, "invalid character: %c\n", s1[i]);
			status = 0;
			goto out;
		}
		/* head and tail are filled... ready to print? */
		if (isalnum(head) && isalnum(tail)) {
			/* check if head and tail make a valid ASCII range */
			if (! ((isupper(head) && isupper(tail))
				|| (islower(head) && islower(tail))
				|| (isdigit(head) && isdigit(tail)))) {
				fprintf(stderr, "bad range %c-%c\n", head, tail);
				head = tail = 0;
				continue;
			}
			/* print the range if next character is a new head */
			if (isalnum(s1[i])) {
				for (; head <= tail; j++, head++) {
					s2[j] = head;
				}
				s2[j] = '\0';
				head = tail = 0;
				i--;
				continue;
			/* range is extended, keep processing input */
			} else if (s1[i] == '-' ) {
				if (s1[i + 1] == '\0') {
					hyphen = 1;
					continue;
				}
				tail = s1[i];
				continue;
			}

		/* only have head so far, keep processing input */
		} else if (isalnum(head)) {
			tail = s1[i];
			continue;
		/* head and tail are empty, keep processing input */
		} else {
			head = tail;
			tail = s1[i];
			continue;
		}

	}
	/* check if head and tail make a valid ASCII range */
	if (! ((isupper(head) && isupper(tail))
		|| (islower(head) && islower(tail))
		|| (isdigit(head) && isdigit(tail)))) {
		fprintf(stderr, "bad range %c-%c\n", head, tail);
		head = tail = 0;
	}
	/* we're out of the main loop. print this last range */
	if (isalnum(head) && isalnum(tail)) {
		for (; head <= tail; j++, head++) {
			s2[j] = head;
		}
		s2[j] = '\0';
	}
	/* print optional trailing hyphen */
	if (hyphen) {
		s2[j++] = '-';
		s2[j] = '\0';
	}
out:
	return status;
}

int
main(void)
{
	int exit_status = 0;
	int i, c;
	char s1[MAXLINE] = {0};
	char s2[MAXLINE] = {0};

	i = c = 0;
	while (i < MAXLINE - 1 ) {
		c = getchar();
		if (c == '\n') break;
		if (c == EOF) break;
		s1[i++] = c;
	}
	s1[++i] = '\0';
	if (! expand(s1, s2)) {
		exit_status = 1;
		goto out;
	}
	printf("%s\n", s2);
out:
	return exit_status;
}
