#include <stdio.h>

int get_line(char line[], int lim);
int itob(char str[], int n, int b, int len);
int atoi(char str[]);
void copy_from_n(char from[], char to[], int len, int n);

#define MAXLINE 80

char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main()
{
        int len, n;
        char line[MAXLINE];

        while ((len = get_line(line, MAXLINE)) > 0) {
		n = atoi(line);
		if (itob(line, n, 16, len) != -1)
	                printf("%s\n", line);
		else
			printf("Invalid Input.\n");
        }

        printf("\n");
        return 0;
}

int get_line(char line[], int lim)
{
	int c, i;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		line[i] = c;
	}

	if (c == '\n')
		line[i++] = c;

	line[i] = '\0';

	if (i >= lim) {
		while ((c = getchar()) != EOF) {
			++i;
		}
	}

	return i;
}

/* Converts string to unsigned int */
int atoi(char str[])
{
	int result = 0;
	char c;

	for (int i = 0; (c = str[i]) != '\n'; ++i) {
		if (c >= '0' && c <= '9') {
			result *= 10;
			result += c - '0';
		} else return -1;
	}

	return result;
}

int itob(char str[], int n, int b, int len)
{
	char result[len];
	int i;

	for (i = 0; i < len; ++i) {
		result[len - 1 - i] = DIGITS[n % b];
		n /= b;
	}
	if (n != 0) return -1;   /* didn't fit in s digits */
	copy_from_n(result, str, i + 1, len - 1 - i);
	return 0;
}

void copy_from_n(char from[], char to[], int len, int n)
{
	for (int i = 0; i < len; ++i) {
		to[i] = from[i + n];
	}
}
