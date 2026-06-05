#include <stdio.h>

void lower(char str[], int len);
int get_line(char line[], int lim);

#define MAXLINE 80

int main(void)
{
    int len;
    char line[MAXLINE];

    while (len = get_line(line, MAXLINE)) {
        lower(line, len);
        printf("%s\n", line);
    }

    return 0;
}

void lower(char str[], int len) {
    for (int i = 0; i < len; ++i) {
        char c = str[i];
        str[i] = (c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c;
    }
}

int get_line(char line[], int lim) {
    int i, c;

    for (i = 0; i < (lim - 1) && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    line[i] = '\0';

    if (c != '\n' && c != EOF) {
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    line[i] = '\0';
    return i;
}
