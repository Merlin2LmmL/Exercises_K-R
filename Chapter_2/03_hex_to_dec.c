#include <stdio.h>

#define MAXLINE 10

int get_line(char line[], int lim);
int htoi(char s[], int len);

/* Lookup table for all ASCII values */
/* Values + 1. Invalid chars are 0   */
static const unsigned char hex_value[256] = {
    ['0'] = 1, ['1'] = 2, ['2'] = 3,
    ['3'] = 4, ['4'] = 5, ['5'] = 6,
    ['6'] = 7, ['7'] = 8, ['8'] = 9,
    ['9'] = 10,

    ['a'] = 11, ['b'] = 12, ['c'] = 13,
    ['d'] = 14, ['e'] = 15, ['f'] = 16,

    ['A'] = 11, ['B'] = 12, ['C'] = 13,
    ['D'] = 14, ['E'] = 15, ['F'] = 16
};

int main(void)
{
    char line[MAXLINE];
    int len;

    while ((len = get_line(line, MAXLINE)) > 0) {
        printf("%d\n", htoi(line, len));
    }

    return 0;
}

int get_line(char line[], int lim) {
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }

    line[i] = '\0';

    if (i == lim - 1) {
        while ((c = getchar()) != '\n' && c != EOF) {
            ++i;
        }
    }

    return i;
}

int htoi(char s[], int len)
{
    int start = len, value = 0;

    for (int i = 0, last_c = ' '; i < len; ++i) {
        char c = s[i];

        if (c == ' '
            || (c == '0' && last_c == ' ')
            || ((c == 'x' || c == 'X') && last_c == '0')) {
            last_c = c;
            continue;
        }

        start = i;
        break;
    }

    for (int i = start; i < len; ++i) {
        int h = hex_value[(unsigned char)s[i]];

        if (h != 0) {
            value = 16 * value + (h - 1);
        } else {
            return -1;
        }
    }

    return value;
}
