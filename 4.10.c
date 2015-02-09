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
void unget(char []);

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
/*
 * 	while j = len = getline(s, 1000)
 * 		while ((type = getop(s, &j) != EOF)) {
 */
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case STR:
			name(s);
			break;
		case NUMBER:
			push(atof(s));
			break;
		case SAVE: /* save a value into a variable named with [a-z] */
			;
			int var = s[0];
			memmove(&s[0], &s[1], sizeof(s) - sizeof(char));
			save(atof(s), var);
			break;
		case RECALL: /* recall a saved variable */
			push(slots[(int)idx[(int)s[0]]]);
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
getop(char s[], int *j)
{
	/* first, run through leading whitespace
	 */
	int i, c;
	while ((s[j]) == ' ' || s[j]  == '\t') ++j; /* skip leading blanks */

	i = 0; /* unused variable? */
	if (s[j] == '-' || s[j] == '+') { /* are '-' and '+' signs or operators? */
		++j;
		if (! isdigit(s[j]) && s[j] != '.') {
			--j;
			return s[j];
		}
	} /* return - or + operators */

	if (s[j] == '^') { /* trying to work with a user variable? 
			   after getting variable name, check if getchar == ' '
			   if true, return RECALL
			   else if value, return SAVE and put value in s
			 */
		++j;
		if (isalpha(s[j])) { /* got var name, proceed */
			if (s[j + 1] == ' ') { /* RECALL */
				s[++j] = '\0';
				return RECALL;
			} else if (isdigit(s[j + 1]) || s[j + 1] == '.') { /* SAVE */
				/* collect integer part of number */
				while (isdigit(s[++j]) ;
				if (s[j] == '.')	/* collect fractional part of number */
					while (isdigit(s[++j]) ;
				s[j] = '\0';
				return SAVE;
			} else if (s[j] != EOF && s[j] != 0) {
				fprintf(stderr, "ya done goofed\n");
				--j; /* replaced ungetch() */
			}
		}
	}

	if (s[j] == '(')
		return PRINT;

	if (isalpha(s[j])) { /* get command word */
		while (isalpha(s[++j])) ;
		s[j] = '\0'; /* this will be wrong if s[j] != ' ' */
		if (s[j] != EOF && s[j] != 0)
			--j;
		return STR;
	} /* could this just read until whitespace? then let main sort it out
	   * in its big switch()?
	   */

	if (! isdigit(s[j]) && s[j] != '.') { /* get all other operators */
		return s[j];	/* not a number */
	}
	if (isdigit(s[j]))	/* collect integer part of number */
		while (isdigit(s[++j];
	if (s[j] == '.')	/* collect fractional part of number */
		while (isdigit(s[++j]; /* used to save last value in c for below */
	s[j] = '\0'; /* this will be wrong if s[j] != ' ' 
	if (c != EOF)
		ungetch(c);
	*/
	return NUMBER;
}

void
ungets(char s[]) {
	int i, c;
	i = 0;
	while (((c = s[i]) != '\0') && c != EOF) {
		ungetch(c);
	}
}
