/* Exercise 4-6. Add commands for handling variables. (It's easy to 
 * provide twenty-six variables with single-letter names.) Add a variable 
 * for the most recently printed value. 
 */
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> /* for isdigit() */
#include <math.h>
#include <string.h>
#define MAXOP 100 /* max size in bytes (char) of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define STR 1 /* signal that a string was read */
#define VAR 2 /* signal that a variable was read */
#define PRINT 3 /* print whole stack */

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

void save(double, int); /* saves a float in a variable named by char */
double slots[25] = {0.0};
const char idx[256] = 
	{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
	6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 
	25, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
	13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
	-1, -1 };

#define MAXVAL 100 /* max depth of val stack */
int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* reverse polish calculator */
int
main(void)
{
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
//		fprintf(stderr, "--> %d\n", type);
		switch (type) {
		case STR:
			name(s);
			break;
		case NUMBER:
			push(atof(s));
			break;
		case VAR:
			;
			/* this doesn't work right because getops doesn't 
			 * respect the whitespace after '^a 123', so you always save
			 * the value 123, and can never do operations with it.
			 */
		if(0) { // don't do this logic here, do it in getops
			int var = s[0];
//			memmove(&s[0], &s[1], sizeof(s) - sizeof(char));
			fprintf(stderr, "s[1] is %d\n", s[1]);
			if (s[1] == ' ') { /* recall value from var */
				push(slots[(int)idx[var]]);
			} else if ((type = getop(s)) == NUMBER) { /* save value to var */
				save(atof(s), var);
			}
		}
			break;
		case PRINT:
			;
			int i = 0;
			printf("stack position %d: %g\n", i, val[0]);
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
save(double x, int c)
{
	slots[(int)idx[c]] = x;
	fprintf(stderr, "saved %g in %c\n", slots[(int)idx[c]], c);
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
	if (sp < MAXVAL) {
		val[sp++] = f;
		fprintf(stderr, "pushed %g\n", f);
	} else {
		fprintf(stderr, "error: stack full, can't push %g\n", f);
	}
}

/* pop: pop and return top value from stack */
double
pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
/*		fprintf(stderr, "error: stack empty\n");
 */
		return 0.0;
	}
}

/* getop: get next character or numeric operand */
int sign;
int
getop(char s[])
{
	fprintf(stderr, "into getop()\n");
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t') { ; /* skip blanks */
	}

	s[1] = '\0';

	i = 0;
	if (c == '-' || c == '+') { /* are '-' and '+' signs or operators? */
		s[++i] = c = getch();
		if (! isdigit(c) && c != '.') {
			ungetch(c);
			return s[0];
		}
	}

	if (c == '^') { /* trying to work with a user variable? 
			   after getting variable name, check if getchar == ' '
			   if true, return RECALL
			   else if value, return SAVE and put value in s
			 */
		s[i] = c = getchar();
		if (isalpha(s[i])) {
			s[++i] = '\0';
			return VAR;
		} else if (c != EOF && c != 0) {
			fprintf(stderr, "ya done goofed\n");
			exit(1);
			ungetch(c);
		}
	}

	if (c == '(')
		return PRINT;

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
