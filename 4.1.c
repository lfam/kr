/* 4.1
 * Write the function strrindex(src, q), which returns the position of the 
 * rightmost occurrence of q in src, or -1 if there is none
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/libkr.h"

#define MAXLINE 1024

int strrindex(char src[], char q[]);

/* Compares from the ends of src and q, returns on first match */
int
strrindex(char src[], char q[])
{
	int srclen = strlen(src);
	int qlen = strlen(q);
	
	int i, j, k;
	for (i = (srclen - 1); i >= 0; i--) {
		for(j = i, k = (qlen - 1); k >= 0 && src[j]==q[k]; j--, k--) ;
		if (k == -1) {
			return (i - (qlen - 1));
		}
	}
	return -1;
}

int
main(int argc, char **argv)
{
	char line[MAXLINE];
	int position;

	if (argc != 2) {
		fprintf(stderr, "ERROR: This program requires the query as argument\n");
		return 1;
	}

	while (getline(line, MAXLINE) > 0) {
		if ((position = strrindex(line, argv[1])) >= 0)
			printf("%d\n", position);
		else
			printf("pattern not found\n");
	}
	return 0;
}
