/* Exercise 4-5. Add access to library functions like sin, exp, and pow. 
 * See <math.h> in Appendix B, Section 4. 
 */
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> /* for isdigit() */
#include <math.h>
#include <string.h>
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define STR 1 /* signal that a string was read */

/* function prototypes */
int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void duplicate_top(void);
void swap(void);
void print_top(void);
void clear_stack(void);
void name(char []);

/* reverse polish calculator */
int
main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case STR:
			name(s);
			break;
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				fprintf(stderr, "error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push((int)pop() % (int)op2);
			else
				printf("warning: modulus of zero\n");
			break;
		case '!':
			clear_stack();
			break;
		case '~':
			swap();
			break;
		case '?':
			print_top();
			break;
		case '#':
			duplicate_top();
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			fprintf(stderr, "error: unknown command: %s\n", s);
			break;
		}
	}
	return 0;
}

void
name(char s[])
{
	if (strcmp(s, "pow") == 0) {
		double op = pop();
		push(pow(pop(), op));
	} else if (strcmp(s, "sin") == 0) {
		push(sin(pop()));
	} else if (strcmp(s, "exp") == 0) {
		push(exp(pop()));
	} else {
		fprintf(stderr, "invalid name: %s\n", s);
	}
}

#define MAXVAL 100 /* max depth of val stack */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* duplicate_top: duplicate the top element of the stack */
void
duplicate_top(void)
{
	if (sp) {
		double dup = pop();
		push(dup);
		push(dup);
	}
}

/* clear_stack: clear the stack */
void
clear_stack(void)
{
	sp = 0;
}

/* print_top: print the top element of stack without popping */
void
print_top(void)
{
	if (sp)
		printf("top of stack:\t%.8g\n", val[sp - 1]);
}

/* swap: swap top two elements of stack */
void
swap(void)
{
	double x, y;
	x = pop();
	y = pop();
	push(x);
	push(y);
}	

/* push: push f onto vlaue stack */

void
push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		fprintf(stderr, "error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double
pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		fprintf(stderr, "error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next character or numeric operand */
int sign;
int
getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t') { ; /* skip blanks */
	}

	s[1] = '\0';

	i = 0;
	if (s[0] == '-' || s[0] == '+') { /* are '-' and '+' signs or operators? */
		s[++i] = c = getch();
		if (! isdigit(c) && c != '.') {
			ungetch(c);
			return s[0];
		}
	}


	if (isalpha(c)) {
		i = 0;
		while ((c = isalpha(s[i++])))
			s[i] = c = getch();
		s[i - 1] = '\0';
		if (c != EOF && c != 0)
			ungetch(c);
		return STR;
	}
	if (! isdigit(c) && c != '.') {
		return c;	/* not a number */
	}
	if (isdigit(c))	/* collect integer part of number */
		while (isdigit(s[++i] = c = getch())) ;
	if (c == '.')	/* collect fractional part of number */
		while (isdigit(s[++i] = c = getch())) ;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define BUFSIZE 100 /* buffer for getch() and ungetch() */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int
getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void
ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters. buffer full\n");
	else
		buf[bufp++] = c;
}
