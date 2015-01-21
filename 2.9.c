#include <stdio.h>
#include "../lib/binary_print.h"

int bitcount(unsigned char);

/* bitcount:  count 1 bits in x */
int kr_bitcount(unsigned x)
{
	int b;
	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;
	return b;
}

/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1) deletes 
 * the rightmost 1-bit in x. Explain why. Use this observation to write a 
 * faster version of bitcount. 
 */
int
bitcount(unsigned char x)
{
	int b;

	for (b = 0; x != 0; x &= (x-1))
		b++;
	return b;
}

int
main(void)
{
	int x = 576;

	int i = 0;
	while (i < 100000000) {
		bitcount(x);
		i++;
	}

	return 0;
}
