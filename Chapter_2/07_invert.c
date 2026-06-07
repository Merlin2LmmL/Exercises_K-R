#include <stdio.h>

int get_line(char line[], int lim);
unsigned invert(unsigned x, int p, int n);
unsigned strtoany(char str[], int b, char charset[], int len);

char BINARY[]  = "01";
char DECIMAL[] = "0123456789";

#define MAXLINE 80
#define INVALID -1

#define TRUE  1
#define FALSE 0

int main(void)
{
	int len, p, n;
	char line[MAXLINE];
	unsigned x;

	len = 1;
	p = n = x = INVALID;

	while (len > 0) {
		if (x == INVALID) {
			printf("Please enter a desired value for x in binary:\n");
			len = get_line(line, MAXLINE);
			x = strtoany(line, 2, BINARY, len);
			continue;
		}

		if (p == INVALID) {
			printf("Please enter a desired value for p in decimal:\n");
			len = get_line(line, MAXLINE);
			p = (int)strtoany(line, 10, DECIMAL, len);
			continue;
		}

		if (n == INVALID) {
			printf("Please enter a desired value for n in decimal:\n");
			len = get_line(line, MAXLINE);
			n = (int)strtoany(line, 10, DECIMAL, len);
			continue;
		}

		if ((x != INVALID) && (p != INVALID) && (n != INVALID)) {
			printf("%b\n", invert(x, p, n));
			x = p = n = INVALID;
		}
	}

	return 0;
}

int get_line(char line[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
		line[i] = c;
	}

	line[i] = '\0';

	return i;
}

unsigned invert(unsigned x, int p, int n)
{
	return (x ^ ((~(~0u << n)) << (p + 1 - n)));
}

unsigned strtoany(char str[], int b, char charset[], int len)
{
	unsigned value = 0;

	for (int i = 0; i < len; ++i) {
		int found = FALSE;
		for (int j = 0; j < b; ++j) {
			if (str[i] == charset[j]) {
				value *= b;
				value += j;
				found = TRUE;
			}
		}
		if (!found) {
			printf("Invalid base %d value!\n", b);
			return INVALID;
		}
	}

	return value;
}
