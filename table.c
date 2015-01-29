#include <stdio.h>

int
main(void)
{
	static const char table[] = {
		[0 ... 255] = -1, 
		['A'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 
		['a'] = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ,10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 
	};
	
	int i = 0;
	printf(" = { ");
	for (; i < 255; i++) {
		printf("%d, ", table[i]);
	}
	printf("%d };\n", table[i]);
	return 0;
}
