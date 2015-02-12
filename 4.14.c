#include <stdio.h>
#define swap(x, y) \
	x = x + y; \
	y = x - y; \
	x = x - y;

int
main(void)
{
	float x = 1.74;
	float y = 3.14;

	printf("%g %g\n", x, y);
	swap(x, y);
	printf("%g %g\n", x, y);

	return 0;
}
