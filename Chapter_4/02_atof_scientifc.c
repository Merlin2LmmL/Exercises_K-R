#include <ctype.h>
#include <stdio.h>

#define MAXLINE 80

int get_line(char line[], int max);
double atof (char string[]);

int main(void)
{
	char line[MAXLINE];

	while (get_line(line, MAXLINE) > 0) {
		printf("%.15g\n", atof(line));
	}

	return 0;
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

/* atof: converts s to double supporting scientific notation */
double atof (char s[])
{
	double val, power;
	int i, sign, scn_sign, scn_power;
	scn_sign = scn_power = 0;

	for (i = 0; isspace(s[i]); ++i)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		++i;
	for (val = 0.0; isdigit(s[i]); ++i)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		++i;
	for (power = 1.0; isdigit(s[i]); ++i) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	if (s[i] == 'e' || s[i] == 'E') {
		++i;
		scn_sign = 1;

		if (s[i] == '+')
			++i;
		else if (s[i] == '-') {
			scn_sign = -1;
			++i;
		}

		for (scn_power = 0; isdigit(s[i]); ++i)
			scn_power = 10 * scn_power + (s[i] - '0');
	}

	if (scn_sign == 1)
		while (scn_power-- > 0)
			val *= 10.0;

	if (scn_sign == -1)
		while (scn_power-- > 0)
			val /= 10.0;

	return sign * val / power;
}
