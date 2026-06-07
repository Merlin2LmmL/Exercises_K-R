#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *expand(char s[]);
char *readline(void);

int main(void)
{
	char *line, *result;
	while ((line = readline()) != NULL) {
		result = expand(line);
		free(line);
		if (result != NULL) {
			printf("%s\n", result);
			free(result);
		} else printf("Unrecognized input.");
	}

	return 0;
}

char *expand(char s[])
{
	int cases = 3;
	int range[3][2] = {
		{ -1, -1 }, /* Starting Letter, Ending Letter */
		{ -1, -1 }, /* Starting Case,   Ending Case   */
		{ -1, -1 }, /* Starting Number, Ending Number */
	};
	int case_max[3][2] = {
		{ 'a', 'z' },
		{ 'A', 'Z' },
		{ '0', '9' }
	};

	size_t len = strlen(s);
	for (int i = 0; i < len - 1; ++i) {
		/* Run through spacing */
		for (; isspace(s[i]); ++i) ;

		/* Process dashes */
		if (s[i] == '-') {
			++i;
			for (int j = 0; j < cases; ++j) {
				if (s[i] >= case_max[j][0] && s[i] <= case_max[j][1]) {
					if (range[j][0] == -1)
						range[j][0] = s[i];
					else if (range[j][1] == -1)
						range[j][1] = s[i];
					else return NULL;
				}
			}
		} else

		/* Process starting Letter / Case / Number */
		for (int j = 0; j < cases; ++j) {
			if (s[i] >= case_max[j][0] && s[i] <= case_max[j][1])
				range[j][0] = s[i];
		}
	}

	/* Determine string size */
	int size = 0;
	for (int i = 0; i < 3; ++i)
		if (range[i][0] != -1 && range[i][1] != -1)
			size += range[i][1] - range[i][0] + 1;
	char *out = malloc(sizeof(char) * (size + 1));

	int i = 0;
	for (int j = 0; j < 3; ++j)
		if (range[j][0] != -1 && range[j][1] != -1)
			for (int k = range[j][0]; k <= range[j][1]; ++k, ++i)
				out[i] = k;

	out[i] = '\0';

	return out;
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
