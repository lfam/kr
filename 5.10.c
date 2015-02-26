#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK 10 /* size of stack */

int
main(int argc, char **argv)
{
	int stack[STACK] = {0};
	int *sp = &stack[0];
	int a, b;

	for (++argv; *argv != NULL; ++argv) {
		switch (*(*argv)) { /* first byte of argv[1] */
		case '0': case '1': case '2': case '3': case '4': case '5': 
		case '6': case '7': case '8': case '9':
negative_number:
			if (sp >= stack + STACK) {
				fprintf(stderr, "error: stack full\n");
				break;
			}
			*sp++ = atoi(*argv);
			break;
		case '+':
			if (sp - stack < 2) {
				fprintf(stderr, "error: <2 operands stacked\n");
				break;
			}
			a = *--sp;
			a += *--sp;
			*sp++ = a;
			break;
		case '*': case 'x':
			if (sp - stack < 2) {
				fprintf(stderr, "error: <2 operands stacked\n");
				break;
			}
			a = *--sp;
			a *= *--sp;
			*sp++ = a;
			break;
		case '-':
			if (*(*argv + 1) != '\0') /* next byte of argument */
				goto negative_number;
			if (sp - stack < 2) {
				fprintf(stderr, "error: <2 operands stacked\n");
				break;
			}
			a = *--sp;
			b = *--sp;
			*sp++ = b - a;
			break;
		case '/':
			if (sp - stack < 2) {
				fprintf(stderr, "error: <2 operands stacked\n");
				break;
			}
			if (*(sp - 1)) { /* check that divisor is not zero */
				a = *--sp;
				b = *--sp;
				*sp++ = b / a;
				break;
			}
			fprintf(stderr, "error: divide by zero\n");
			break;
		default:
			fprintf(stderr, "invalid input: %s\n", *argv);
			break;
		}
	}

	printf("%d\n", *stack); /* *stack or *--sp? ... */

	int i;
	for (i = 0, sp = &stack[0]; i < STACK; ++i, *++sp) {
		fprintf(stderr, "%d %d\n", i, *sp);
	}

	return 0;
}
/*
    While there are input tokens left
        Read the next token from input.
        If the token is a value
            Push it onto the stack.
        Otherwise, the token is an operator (operator here includes both operators and functions).
            It is known a priori that the operator takes n arguments.
            If there are fewer than n values on the stack
                (Error) The user has not input sufficient values in the expression.
            Else, Pop the top n values from the stack.
            Evaluate the operator, with the values as arguments.
            Push the returned results, if any, back onto the stack.
    If there is only one value in the stack
        That value is the result of the calculation.
    Otherwise, there are more values in the stack
        (Error) The user input has too many values.
*/
