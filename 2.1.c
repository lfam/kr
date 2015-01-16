/*
 * Determine the ranges of char, short, int, and longs, signed and unsigned.
 * Get the values from the headers and by computation.
 */
#include <stdio.h>
#include <limits.h>

void naive_signed_char();
signed char naive_signed_char_max();
void naive_unsigned_char();
unsigned char naive_unsigned_char_max();
void naive_unsigned_int();
unsigned int naive_unsigned_int_max();
void header();

void
header()
{
	printf("from header:\n");
	printf("signed char min: %d\n", CHAR_MIN);
	printf("signed char max: %d\n", CHAR_MAX);
	putchar('\n');
	
	printf("from header:\n");
	printf("unsigned char min: %d\n", 0);
	printf("unsigned char max: %d\n", UCHAR_MAX);
	putchar('\n');
	
	printf("from header:\n");
	printf("short min: %d\n", SHRT_MIN);
	printf("short max: %d\n", SHRT_MAX); 
	putchar('\n');

	printf("from header:\n");
	printf("unsigned short min: %d\n", 0);
	printf("unsigned short max: %d\n", USHRT_MAX);
	putchar('\n');

	printf("from header:\n");
	printf("int min: %d\n", INT_MIN);
	printf("int max: %d\n", INT_MAX);
	putchar('\n');

	printf("from header:\n");
	printf("unsigned int min: %d\n", 0);
	printf("unsigned int max: %u\n", UINT_MAX);
	putchar('\n');

	printf("from header:\n");
	printf("long min: %ld\n", LONG_MIN);
	printf("long max: %ld\n", LONG_MAX);
	putchar('\n');

	printf("from header:\n");
	printf("unsigned long min: %d\n", 0);
	printf("unsigned long max: %lu\n", ULONG_MAX);
}

signed char
naive_signed_char_max()
{
	signed char c = 0;
	signed char max = c;

	while (++c > 0) {
		max = c;
	}
	return max;
}

void
naive_signed_char()
{
	signed char max = naive_signed_char_max();
	signed char c = max;
	signed char min = 4;

	while (--c != max) {
		min = c;
	}
	printf("min %d\n", min);
	printf("max %d\n", max);
}

unsigned int 
naive_unsigned_int_max()
{
	unsigned int i = 1;
	unsigned int max = 1;
	
	while (++i > 0) {
		max = i;
	}
	return max;
}

void
naive_unsigned_int()
{
	unsigned int max = naive_unsigned_int_max();
	unsigned int ui = max;
	unsigned int min = 4; /* junk value for sanity check */

	while (--ui != max) {
		min = ui;
	}
	printf("min %u\n", min);
	printf("max %u\n", max);
}

unsigned char 
naive_unsigned_char_max()
{
	unsigned char uc = 1;
	unsigned char max = 1;
	
	while (++uc > 0) {
		max = uc;
	}
	return max;
}

void
naive_unsigned_char()
{
	unsigned char max = naive_unsigned_char_max();
	unsigned char uc = max;
	unsigned char min = 4; /* junk value for sanity check */

	while (--uc != max) {
		min = uc;
	}
	printf("min %u\n", min);
	printf("max %u\n", max);
}

int
main() {
/*
	printf("computed values\n");
	printf("---------------\n");
	putchar('\n');

	printf("signed char:\n");
	naive_signed_char();
	putchar('\n');

	printf("unsigned char:\n");
	naive_unsigned_char();
	putchar('\n');

	printf("from header\n");
	printf("-----------\n");
 	header();
*/
	unsigned char c;
	unsigned short s;
	unsigned int i;
	unsigned long l;

	c = ~0;
	c >>= 1;
	printf("signed char:   %4d,           %4d\n",-c - 1, c);
	printf("SCHAR_MIN:     %4d, SCHAR_MAX %4d\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char: %4u,           %4u\n", 0, c * 2 + 1);
	printf("UCHAR_MAX:                     %4u\n", UCHAR_MAX);
	putchar('\n');

	s = ~0;
	s >>= 1;
	printf("signed short:   %6d,			%6d\n",-s - 1, s);
	printf("SHRT_MIN:	%6d, SHRT_MAX	%6d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short:	%6u,			%6u\n", 0, s * 2 + 1);
	printf("USHRT_MAX:				%6u\n", USHRT_MAX);
	putchar('\n');

	i = ~0;
	i >>= 1;
	printf("signed integer:	%11d,		%11d\n",-i - 1, i);
	printf("INT_MIN:	%11d, INT_MAX	%11d\n", INT_MIN, INT_MAX);
	printf("unsigned int:	%11u,		%11u\n", 0, i * 2 + 1);
	printf("UINT_MAX:				%11u\n", UINT_MAX);
	putchar('\n');

	l = ~0;
	l >>= 1;
	printf("signed long:	%11ld,           %11ld\n",-l - 1, l);
	printf("LONG_MIN:	%11ld, LONG_MAX	%11ld\n", LONG_MIN, LONG_MAX);
	printf("unsigned long:	%11u,           %11lu\n", 0, l * 2 + 1);
	printf("ULONG_MAX:                     %11lu\n", ULONG_MAX);

	return 0;
}
/*
	c = ~0;
	c >>= 1;
	printf("signed char:   %4d,           %4d\n",-c-1,c);
	printf("SCHAR_MIN:     %4d, SCHAR_MAX %4d\n",SCHAR_MIN,SCHAR_MAX);
	printf("unsigned char: %4u,           %4u\n",0,c*2+1);
	printf("UCHAR_MAX:                     %4u\n",UCHAR_MAX);
	putchar('\n');
*/
