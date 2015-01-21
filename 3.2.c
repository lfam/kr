#include <stdio.h>

#define NL 10
#define TAB 9
#define BSLASH 92

void escape(char [], char []);
void unescape(char [], char []);

/* 3.2 copy t to s, replacing newlines and tabs with \n and \t */
void
escape(char s[], char t[])
{
	int i = 0;
	int j = 0;
	while (t[i] != '\0') {
		switch (t[i]) {
		case NL:
			i++;
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		case TAB:
			i++;
			s[j++] = '\\';
			s[j++] = 't';
		default:
			s[j++] = t[i++];
			break;
		}
	}
}

void
unescape(char s[], char t[])
{
	int i = 0;
	int j = 0;
	while (t[i] != '\0') {
		if (t[i] == '\\') {
			switch (t[++i]) {
			case 'n':
				s[j++] == NL;
				i++;
				break;
			case 't':
				s[j++] == TAB;
				i++;
				break;
			default:
				s[j++] == '\\';
				s[j++] == t[i];
				break;
			}
		} else {
			s[j++] = t[i++];
		}
	}
}

int
main(void)
{

	char from[1024] = "This 	\n		is \nmy string";
	printf("%s\n", from);
	char to[1024] = {0};
	escape(to, from);
	printf("%s\n", to);
	unescape(from, to);
	printf("%s\n", from);
	return 0;
}
