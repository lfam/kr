#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> /* for isdigit() */
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

/* function prototypes */
int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

/* reverse polish calculator */
int
main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
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
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push((int)pop() % (int)op2);
			else
				printf("error: zero divisor\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

/* push: push f onto vlaue stack */
#define MAXVAL 100 /* max depth of val stack */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

void
push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
double
pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next character or numeric operand */
int sign;
int
getop(char s[])
{
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t') ; /* skip blanks */

	s[1] = '\0';
	if (! isdigit(c) && c != '.')
		return c;	/* not a number */
	i = 0;
	if (isdigit(c))	/* collect integer part of number */
		while (isdigit(s[++i] = c = getch())) ;
	if (c == '.')	/* collect fractional part of number */
		while (isdigit(s[++i] = c = getch())) ;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

int
getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

#define BUFSIZE 100 /* buffer for getch() and ungetch() */
void
ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters. buffer full\n");
	else
		buf[bufp++] = c;
}
