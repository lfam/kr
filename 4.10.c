/* Exercise 4-10. An alternate organization uses getline to read an entire 
 * input line; this makes getch and ungetch unnecessary. Revise the calculator
 * to use this approach. 
 */

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> /* for isdigit() */
#include <math.h>
#include <string.h>
#define MAXOP 100 /* max size in bytes (char) of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define STR 1 /* signal that a string was read */
#define SAVE 2 /* signal save a value */
#define PRINT 3 /* print whole stack */
#define RECALL 4 /* signal to push a saved value onto the stack */

/* function prototypes */
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void duplicate_top(void);
void swap(void);
void print_top(void);
void clear_stack(void);
void name(char []);
void unget(char []);
int getop(char *s, char *ret);

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
	ssize_t len = 0;
	char *s = NULL;
	char *ret = NULL;

	while ((len = getline(&s, 0, stdin)) > 0) {
		while ((type = getop(s, ret)) != EOF) {
			switch (type) {
			case STR:
				if (ret != NULL)
					name(ret);
				break;
			case NUMBER:
				if (ret != NULL)
					push(atof(ret));
				break;
			case SAVE: /* save a value into a variable named with [a-z] */
				if (ret != NULL) {
					int var = (int)*ret;
					save(atof(++ret), var);
				}
				break;
			case RECALL: /* recall a saved variable */
				if (ret != NULL)
					push(slots[(int)idx[(int)*ret]]);
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
				fprintf(stderr, "error: unknown command: %s\n", ret);
				break;
			}
			++s;
		}
	}
	return 0;
}

/* getop: get next character or numeric operand */
/* expects a whitespace (' ' or '\t') delimited list of operators and operands,
 * terminated with a '\n'
 */
int
getop(char *s, char *ret)
{
	ret = s;

	/* first, run through leading whitespace */
	while ((*s) == ' ' || *s  == '\t') ++s; /* skip leading blanks */

	if (*s == '-' || *s == '+') { /* are '-' and '+' signs or operators? */
		++s;
		if (! isdigit(*s) && *s != '.') {
			*++s = '\0';
			return (int)*ret;
		}
	} /* return - or + operators */

	if (*s == '^') { /* trying to work with a user variable? 
			   after getting variable name, check if getchar == ' '
			   if true, return RECALL
			   else if value, return SAVE and put value in s
			 */
		++s;
		if (isalpha(*s)) { /* got var name, proceed */
			if (*s + 1 == ' ') { /* RECALL */
				*++s = '\0';
				return RECALL;
			} else if (isdigit(*s + 1) || *s + 1 == '.') { /* SAVE */
				/* collect integer part of number */
				while (isdigit(*++s)) ;
				if (*s == '.')	/* collect fractional part of number */
					while (isdigit(*++s)) ;
				*s = '\0';
				return SAVE;
			} else if (*s != EOF && *s != 0) {
				fprintf(stderr, "ya done goofed\n");
				--s; /* replaced ungetch() */
			}
		}
	}

	if (*s == '(') {
		*++s = '\0';
		return PRINT;
	}

	if (isalpha(*s)) { /* get command word */
		while (isalpha(*++s)) ;
		if (*s == ' ') {
			*s = '\0';
		} else if (*s != EOF && *s != 0) {
			fprintf(stderr, "ya done goofed\n");
			--s;
		}
		return STR;
	} /* could this just read until whitespace? then let main sort it out
	   * in its big switch()?
	   */

	if (! isdigit(*s) && *s != '.') { /* get all other operators */
		*(s + 1) = '\0';
		return (int)*ret;	/* not a number */
	}

	if (isdigit(*s)) {	/* collect integer part of number */
		while (isdigit(*++s));
	}
	if (*s == '.') {	/* collect fractional part of number */
		while (isdigit(*++s)); /* used to save last value in c for below */
	}
	*s = '\0';
	return NUMBER;
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
