#include <stdio.h>

#define MAXLINE 80

int get_line(char line[], int len);
void reverse(char line[], int lim);

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) > 0) {
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

    reverse(line, i - 1);

    line[i] = '\0';

    return i;
}

void reverse(char line[], int len)
{
    char tmp;

    for (int i = 0, j = len - 1; i < j; ++i, --j) {
        tmp = line[i];
        line[i] = line[j];
        line[j] = tmp;
    }
}
