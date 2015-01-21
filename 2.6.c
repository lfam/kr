#include <stdio.h>
#include "../lib/binary_print.h"

unsigned char getbits(unsigned char, int, int);
unsigned char setbits(unsigned char, int, int, unsigned char);

/* getbits: get n bits from position p */
unsigned char 
getbits(unsigned char x, int p, int n)
{
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

/* setbits:
 * returns x with the n bits that begin at position p set to the rightmost bits
 * of y, leaving the other bits unchanged
 */
unsigned char
setbits(unsigned char x, int p, int n, unsigned char y)
{
	unsigned char mask;
	unsigned int offset = (p + 1 - n);

   	mask = ~(~0 << n); 
	y = (y & mask) << offset;
	x = ~(mask << offset);

	return (x | y);
}

int
main(void)
{
	printf("76543210 legend\n");

	unsigned char x = ~0;
	fprintf(stderr, "x is %d\n", x);
	printf(PRINTF_BYTE" x\n", BYTE(x));

	unsigned char y = 101;
	fprintf(stderr, "y is %d\n", y);
	printf(PRINTF_BYTE" y\n", BYTE(y));

	unsigned char c = setbits(x, 3, 3, y);

	fprintf(stderr, "c is %d\n", c);
	printf(PRINTF_BYTE" after\n", BYTE(c));

	return 0;
}
