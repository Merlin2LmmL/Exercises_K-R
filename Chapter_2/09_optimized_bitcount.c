#include <stdio.h>

int get_line(char line[], int lim);
int bitcount(unsigned x);
unsigned strtoany(char str[], int b, char charset[], int len);

char BINARY[]  = "01";

#define MAXLINE 80
#define INVALID -1

#define TRUE  1
#define FALSE 0

int main(void)
{
	int len = 1;
	char line[MAXLINE];
	unsigned x = INVALID;

	while (len > 0) {
		if (x == INVALID) {
			printf("Please enter a desired value for x in binary:\n");
			len = get_line(line, MAXLINE);
			x = strtoany(line, 2, BINARY, len);
			continue;
		}

		if (x != INVALID) {
			printf("%d\n", bitcount(x));
			x = INVALID;
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

int bitcount(unsigned x)
{
	int b;

	/**
	 *  We mask x with itself with its rightmost 1 bit
	 *  deleted and delete all resulting 1 bits in the
	 *  process, resulting in couting the rightmost 1
	 *  bit each iteration.
	 */
	for (b = 0; x != 0; ++b)
		x &= (x - 1);

	return b;
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
