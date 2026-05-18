#include <stdio.h>

#define MAXLINE 100

/**
 *  named get_line(), because getline() would
 *  interfer with stdio libs getline()
 */
int get_line(char line[], int lim);
void copy(char from[], char to[]);

int main(void)
{
    int len, max = 0;
    char longest[MAXLINE], line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > max) {
            copy(line, longest);
            max = len;
        }
        printf("%s\n", longest);
    }

    printf("\n");

    return 0;
}

/**
 *  Outputs one line at a time to line[].
 *  Returns line length.
 */
int get_line(char line[], int lim)
{
    int c, i;

    for (i = 0; i < lim && (c = getchar()) != '\n' && c != EOF; ++i) {
        line[i] = c;
    }

    line[i] = '\0';

    return i;
}

void copy(char from[], char to[])
{
    int i = 0;

    while ((to[i] = from[i]) != '\0')
        ++i;
}
