#include <stdio.h>

#define MAXLINE 50

enum boolean {
    FALSE,
    TRUE
};

int get_line(char line[], int lim);
int squeeze(char s1[], char s2[], int len1, int len2);

int main(void)
{
    char line[MAXLINE];
    int len;

    while ((len = get_line(line, MAXLINE)) > 0) {
        len = squeeze(line, "0123456789", len, 10);
        printf("%s\n", line);
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

int squeeze(char s1[], char s2[], int len1, int len2)
{
    int i, j, has_c;
    has_c = FALSE;

    for (i = j = 0; i < len1; ++i) {
        for (int k = 0; k < len2; ++k) {
            if (s1[i] == s2[k]) has_c = TRUE;
        }
        if (!has_c) {
            s1[j++] = s1[i];
        }
        has_c = FALSE;
    }
    s1[j] = '\0';

    return j;
}
