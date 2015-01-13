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
	printf("computed values\n");
	printf("---------------\n");
	putchar('\n');

	printf("signed char:\n");
	naive_signed_char();
	putchar('\n');

	printf("unsigned char:\n");
	naive_unsigned_char();
	putchar('\n');

	printf("unsigned int:\n");
	/* SLOW!!!!!
	naive_unsigned_int();
	*/
	putchar('\n');

	printf("from header\n");
	printf("-----------\n");
 	header();
	return 0;
}
