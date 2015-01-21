#include <stdio.h>
/*
 * 3.1 improve the given binary search algorithm
 */

int binsearch(int, int [], int);
int kr_binsearch(int, int [], int);

int
kr_binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else	/* found match */
			return mid;
	}
	return -1; /* no match */
}

int
binsearch(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
   	mid = (low + high) / 2;
	while ((low <= high) && (x != v[mid])) {
		if (x < v[mid]) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
		mid = (low + high) / 2;
	}
	if (x == v[mid])
		return mid;
	else
		return -1;
}

int
binsearch2(int x, int v[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}

	if (x == v[low])
		return low;
	else
		return -1;
}

int
main(void)
{
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int n = sizeof(a) / sizeof(int);
	int q = -1;
	scanf("%d", &q);
	int exit_status = 0;

	int idx = -1;
	if ((idx = binsearch2(q, a, n)) != -1) {
		printf("at %d\n", idx);
		exit_status = 0;
	} else {
		printf("not found\n");
		exit_status = 1;
	}
	return exit_status;
}
