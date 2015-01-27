/* 4.2
 * Extend atof() to handle scientific notation of the form
 * 	123.45e-6
 * where a floating point number may be followed by e or E and an optionallly
 * signed exponent.
 */
#include <stdio.h>
#include <ctype.h>
#include "lib/libkr.h"

#define MAXLINE 100

double kr_atof(char []);
double atof(char[]);

/* atof: convert string s to double */
double
kr_atof(char s[])
{
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1; /* record sign */

	if (s[i] == '+' || s[i] == '-') /*skip sign */
		i++;

	for (val = 0.0; isdigit(s[i]); i++) /* while input is a number */
		val = 10.0 * val + (s[i] - '0'); /* multiply val by ten and add digit */

	if (s[i] == '.') /* process decimal point */
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0'); /* as above */
		power *= 10.0; /* multiply power by ten */
	}
	return sign * val / power; /* apply sign and divide by power */
}

double
atof(char s[])
{
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++) /* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1; /* record sign */

	if (s[i] == '+' || s[i] == '-') /*skip sign */
		i++;

	for (val = 0.0; isdigit(s[i]); i++) /* while input is a number */
		val = 10.0 * val + (s[i] - '0'); /* multiply val by ten and add digit */

	if (s[i] == '.') /* process decimal point */
		i++;

	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0'); /* as above */
		power *= 10.0; /* multiply power by ten */
	}

	int enot;
	double p, base;
	if (s[i] == 'e' || s[i] == 'E') {
		++i;
	} else {
		return sign * val / power;
	}
	base = (s[i] == '-') ? 0.1 : 10;
	if (s[i] == '+' || s[i] == '-')
		i++;

	for (enot = 0; isdigit(s[i]); i++)
		enot = 10 * enot + (s[i] - '0');

	for (p = 1; enot > 0; --enot) {
		p = p * base;
		fprintf(stderr, "power is %f\n", p);
	}

	if (s[i] != '\0' && s[i] != '\n') 
		fprintf(stderr, "stray input at end: %d\n", s[i]);

	return (sign * (val / power)) * p;
}

/* rudimentary calculator */
int
main(void)
{
	double sum, ret;
	char line [MAXLINE];
	double atof(char[]);

	sum = ret = 0;
	while (getline(line, MAXLINE) > 0) {
		printf("\t%f\n", sum += atof(line));
	}
	return 0;
}
