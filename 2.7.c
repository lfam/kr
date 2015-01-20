#include <stdio.h>
#include "../lib/binary_print.h"

unsigned char invert(unsigned char, int, int);

unsigned char
invert(unsigned char x, int p, int n)
{
	unsigned char mask;
	mask = ~(~0 << n) << (p + 1 - n);
	return ((x & ~mask) | (~x & mask));
}

int
main(void)
{
	printf("76543210 legend\n");

	unsigned char x = 93;
	printf(PRINTF_BYTE" x\n", BYTE(x));

	unsigned char c = invert(x, 5, 2);

	printf(PRINTF_BYTE" after\n", BYTE(c));

	return 0;
}
