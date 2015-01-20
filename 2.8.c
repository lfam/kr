#include <stdio.h>
#include <limits.h>
#include "../lib/binary_print.h"

int rightrot(int, int);

/*
 * Exercise 2-8. Write a function rightrot(x,n) that returns the value of 
 * the integer x rotated to the right by n positions. 
 */
int
rightrot(int x, int n)
{
	int mask, buf;
	mask = ~(~0 << n);
	buf = ((x & mask) << ((sizeof(buf) * CHAR_BIT) - n));
	x >>= n;

	return (x | buf);
}

int
main(int argc, char **argv)
{
	int x = 33318;
	int n = 5;
	printf(PRINTF_BYTE32"\n", BYTE32(x));
	x = rightrot(x, n);
	printf(PRINTF_BYTE32"\n", BYTE32(x));
	return 0;
}
