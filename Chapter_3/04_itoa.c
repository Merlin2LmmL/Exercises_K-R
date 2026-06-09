
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char *itoa(int n);
int strtoi(char s[], int b, int *value);
char *readline(void);

int main(void)
{
	char *line;

	while ((line = readline()) != NULL) {
		int num;

		if (strtoi(line, 10, &num) != -1) {
			char *result;
			if ((result = itoa(num)) != NULL) {
				printf("%s\n", result);
				free(result);
			}

		} else printf("Invalid Input\n");

		free(line);
	}

	printf("\n");
	return 0;
}

char *itoa(int n)
{
	if (n == 0) {
    		char *s = malloc(2);
    		s[0] = '0';
    		s[1] = '\0';
    		return s;
	}

	int length = floor(log10(abs(n))) + 1;
	int is_negative = (n < 0) ? 1 : 0;
	char *s = malloc(sizeof(char) * (length + is_negative + 1));

	if (s == NULL)
		return NULL;

	n = abs(n);

	for (int i = (length - 1) + is_negative; i >= is_negative; --i) {
		s[i] = n % 10 + '0';
		n /= 10;
	}

	if (is_negative)
		s[0] = '-';

	s[length + is_negative] = '\0';

	return s;
}

int strtoi(char s[], int b, int *value)
{
	*value = 0;
	int is_negative = 0; /* default positive */

	for (int i = 0; s[i] != '\0' && s[i] != '\n'; ++i) {
		int c = s[i];
		if (!((c >= '0' && c <= '9') || (c == '-' && i <= 2)))
			return -1;

		if (c == '-') {
			is_negative = !is_negative;
		} else {
			*value *= b;
			*value += c - '0';
		}
	}

	if (is_negative)
		*value *= -1;

	return 0;
}

char *readline(void) {
	size_t size = 8;
	size_t len = 0;

	char *line = malloc(8 * sizeof(char));
	if (!line) return NULL;

	int c;

	while ((c = getchar()) != EOF && c != '\n') {
		if (len + 1 >= size) {
			size *= 2;
			char *tmp = realloc(line, size);
			if (!tmp) {
				free(line);
				return NULL;
			}
		line = tmp;
		}

		line[len++] = (char)c;
	}

	if (c == EOF && len == 0) {
		free(line);
		return NULL;
	}

	line[len] = '\0';

	return line;
}
