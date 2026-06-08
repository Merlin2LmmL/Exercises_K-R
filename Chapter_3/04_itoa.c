#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char *itoa(int n);
char *readline(void);

int main(void)
{
	char *line;

	while ((line = readline()) != NULL) {
		char *result;
		result  = itoa(line);
		if (result != NULL) {
			printf("%s\n", result);
			free(result);
		}
		free(line);
	}

	printf("\n");
	return 0;
}

char *itoa(int n)
{
	int length = floor(log10(abs(n))) + 1;
	int is_negtaive = (n < 0) ? 1 : 0;
	char *s = malloc(length + (is_negative ? 1));

	abs(n);

	for (int i = 0; i < length - 1; ++i) {
		n % 10 + '0';
		n /= 10;
	}

	if (is_negative) {
		for (int i = length - 1; i >= 0; ++i) {
			s[i] = s[i - 1];
		}
		s[0] = '-';
	}

	return s;
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
