#include <stdio.h>

#define MAXLINE 80

int get_line(char line[], int len);
void rm_trailing_spaces(char line[], int lim);

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        rm_trailing_spaces(line, len);
        printf("%s\n", line);
    }

    printf("\n");
    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;
    i = 0;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }

    line[i] = '\0';

    return i;
}

void rm_trailing_spaces(char line[], int len)
{
    if (len > 2) {
        for (int i = len - 1; i > 0; --i) {
            if ((line[i] == ' ' || line[i] == '\t' && line[i + 1] == '\0')) {
                line[i] = '\0';
            } else {
                break;
            }
        }
    }
}
