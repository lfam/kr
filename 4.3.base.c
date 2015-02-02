#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> /* for isdigit() */

#define MAXVAL 100 /* max depth of val stack */
#define BUFSIZE 100 /* buffer for getch() and ungetch() */
#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */

/* function prototypes */
int getop(char []);
int push(double val[], int sp, double f);
double pop(double val[], int *sp);
int getch(char buf[], int *bufp);
int ungetch(int c, char buf[], int bufp);

/* reverse polish calculator */
int
main(void)
{
	double val[MAXVAL]; /* value stack */
	int sp = 0; /* next free stack position */
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			sp = push(val, sp, atof(s));
			break;
		case '+':
			sp = push(val, sp, (pop(val, &sp) + pop(val, &sp)));
			break;
		case '*':
			sp = push(val, sp, (pop(val, &sp) * pop(val, &sp)));
			break;
		case '-':
			op2 = pop(val, &sp);
			sp = push(val, sp, (pop(val, &sp) - op2));
			break;
		case '/':
			op2 = pop(val, &sp);
			if (op2 != 0.0)
				sp = push(val, sp, (pop(val, &sp) / op2));
			else
				printf("error: zero divisor\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop(val, &sp));
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

/* push: push f onto value stack, return next free stack position */
int
push(double val[], int sp, double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
	return sp;
}

/* pop: pop and return top value from stack */
double
pop(double val[], int *sp)
{
	if (*sp > 0)
		return val[--*sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next character or numeric operand */
int
getop(char s[])
{
	char buf[BUFSIZE]; /* buffer for ungetch */
	int bufp = 0; /* next free position in buf */
	int i, c;

	while ((s[0] = c = getch(buf, &bufp)) == ' ' || c == '\t') ; /* skip blanks */

	s[1] = '\0';
	if (! isdigit(c) && c != '.')
		return c;	/* not a number */
	i = 0;
	if (isdigit(c))	/* collect integer part of number */
		while (isdigit(s[++i] = c = getch(buf, &bufp))) ;
	if (c == '.')	/* collect fractional part of number */
		while (isdigit(s[++i] = c = getch(buf, &bufp))) ;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c, buf, bufp);
	return NUMBER;
}

int /* get a (possibly pushed-back) character */
getch(char buf[], int *bufp)
{
	return (*bufp > 0) ? buf[--*bufp] : getchar();
}

int /* push character back on input, return next free buf position */
ungetch(int c, char buf[], int bufp)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters. buffer full\n");
	else
		buf[(bufp)++] = c;
	return bufp;
}
