#include <stdio.h>

#define MAXLINE 100
const int TABPOS = 8;

int get_line(char line[], int lim);
void detab(char line[], int len, int lim);
int shift(char line[], int len, int pos, int qty, int lim);

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
        detab(line, len, MAXLINE);
        printf("%s\n", line);
    }
}

int get_line(char line[], int lim)
{
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    line[i] = '\0';

    if (i == lim) {
        while ((c = getchar()) != EOF && c != '\n') {
            ;
        }
    }

    return i;
}

void detab(char line[], int len, int lim)
{
    for (int i = 0; i < len; ++i) {
        if (line[i] == '\t') {
            len = shift(line, len, i, TABPOS - (i % TABPOS) - 1, lim);
            line[i] = ' ';
        }
    }
    line[len] = '\0';
}

int shift(char line[], int len, int pos, int qty, int lim)
{
    /* only shifts to the right */
    if (qty < 0) return len;

    for (int i = 0; i < qty; ++i) {
        if (len > lim) return len;
        for (int j = len - 1; j >= pos; --j) {
            line[j + 1] = line[j];
            line[j] = ' ';
        }
        ++len;
    }

    return len;
}
