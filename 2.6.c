#include <stdio.h>
#include "../lib/binary_print.h"
#include <stdlib.h>

/* getbits: get n bits from position p */
unsigned char 
getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

int
main(int argc, char **argv)
{
	printf("76543210 legend\n");
	unsigned char x = 101;
	fprintf(stderr, "x is %d\n", x);
	printf(PRINTF_BYTE"\n", BYTE(x));
	unsigned char c = getbits(x, 8, 9);
	fprintf(stderr, "c is %d\n", c);
	printf(PRINTF_BYTE"\n", BYTE(c));
	return 0;
}
