/* reverse:  reverse string s in place */
void reverse(char s[], int len)
{
	int c, i, j;

	for (i = 0, j = len - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
