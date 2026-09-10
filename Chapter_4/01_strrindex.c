#include <stdio.h>

#define MAXLINE 80

int get_line(char line[], int max);
int strrindex(char source[], char pattern[]);
int getlen(char string[]);

char pattern[] = "ERL";

int main(void)
{
	char line[MAXLINE];
	int found = 0;

	while (get_line(line, MAXLINE) > 0) {
		if (strrindex(line, pattern) >= 0) {
			printf("%s\n", line);
			++found;
		}
	}

	return found;
}

/* get_line: get line into s, return length */
int get_line(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}

/*strrindex: returns rightmost index of t in s, -1 if none */
int strrindex(char s[], char t[])
{
	int i, j, k;

	for (i = getlen(s); i >= 0; --i) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k) ;

		if (k > 0 && t[k] == '\0') {
			return i;
		}
	}

	return -1;
}

int getlen(char s[])
{
	int i = 0;

	for (; s[i] != '\0'; ++i) ;

	return i;
}
