#include <stdio.h>

#define MAXLINE 51

/**
 *  named get_line(), because getline() would
 *  interfer with stdio libs getline()
 */
int get_line(char line[], int lim);
void copy(char to[], char from[]);

int main(void)
{
    int len, max = 0;
    char longest[MAXLINE], line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > max) {
            copy(longest, line);
            max = len;
        }
    }

    if (max > 0) {
        printf("\nLongest Line (%d chars): %s\n", max, longest);
    }

    return 0;
}

/**
 *  Outputs one line at a time to line[].
 *  Returns line length.
 */
int get_line(char line[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
        line[i] = c;
    }

    line[i] = '\0';

    // Run thorugh debugging
    if (i == lim - 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
            ++i;
        }
    }

    return i;
}

void copy(char to[], char from[])
{
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}
