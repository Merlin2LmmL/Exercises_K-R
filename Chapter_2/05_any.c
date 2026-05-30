#include <stdio.h>

#define MAXLINE 80

enum boolean {
    FALSE,
    TRUE
};

int get_line(char line[], int lim);
int any(char s1[], char s2[], int len1, int len2);

int main(void)
{
    char line[MAXLINE];
    int len;

    while ((len = get_line(line, MAXLINE)) > 0) {
        printf("%d\n", any(line, "0123456789", len, 10));
    }

    return 0;
}

int get_line(char line[], int lim) {
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }

    line[i] = '\0';

    return i;
}

int any(char s1[], char s2[], int len1, int len2)
{
    for (int i = 0; i < len1; ++i) {
        for (int j = 0; j < len2; ++j) {
            if (s1[i] == s2[j]) return i;
        }
    }

    return -1;
}
