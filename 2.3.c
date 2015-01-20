#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAXLINE 1024

int hex_validator(unsigned const char *, int);
long long int htoi(unsigned const char *);
long long int my_exp(int, int);

int
hex_validator(unsigned const char *s, int len)
{
	int retval = 0;
	int i = 0;

	/* process minus sign */
	if (s[i] == '-') {
		i++;
	}

	/* process 0x or 0X hex identifier */
	if (s[i] == '0') {
		i++;
		if ((s[i] != 'x') && (s[i] != 'X')) {
			goto out;
		} else {
			i++;
		}
	}

	while (i < len - 1) {
		if (
			(((s[i] >= '0') && (s[i] <= '9')) || 
			((s[i] >= 'A') && (s[i] <= 'F')) || 
			((s[i] >= 'a') && (s[i] <= 'f'))))
		{
			i++;
		} else {
			break;
		}
	}
	if (i == len - 1) retval = 1;
out:
	return retval;
}

long long int
my_exp(int base, int exp)
{
	long long int value = 1;
	while (exp != 0) {
		value *= base;  /* value = value*base; */
		--exp;
	}
	return value;
}

/* 
 * http://stackoverflow.com/questions/10324/how-can-i-convert-a-hexadecimal-number-to-base-10-efficiently-in-c
 * @brief convert a hexidecimal string to a signed long
 * will not produce or process negative numbers except 
 * to signal error.
 * 
 * @param hex without decoration, case insensative. 
 * 
 * @return -1 on error, or result (max sizeof(long)-1 bits)
 */
/*
   static const long gnu_hextable[] = {
   [0 ... 255] = -1, 
   ['0'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 
   ['A'] = 10, 11, 12, 13, 14, 15,
   ['a'] = 10, 11, 12, 13, 14, 15
};
*/
static const long hextable[] =  {
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5, 
6, 7, 8, 9, -1, -1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
-1, -1, -1
};

long long int htoi(unsigned const char *hex) {
	long long ret = 0;
	while (*hex && ret >= 0) {
		ret = (ret << 4) | hextable[*hex++];
	}
	return ret; 
}

int
main()
{
	int exit_status = 0;

	int i = 0;
	unsigned char s[MAXLINE];

	int c;
	while (i < MAXLINE - 1) {
		c = getchar();
		if (c == '\n') break;
		if (c == '\0') break;
		if (c == EOF) break;
		s[i++] = c;
	}
	s[i++] = '\0';
/*
	if (! hex_validator(s, i)) {
		fprintf(stderr, "not valid hex!\n");
		exit_status = 1;
		goto out;
	} 
*/
	long long int result = htoi(s);
	if (result < 0) {
		exit_status = 1;
		goto out;
	}
	printf("%lld\n", result);

out:
	return exit_status;
}
