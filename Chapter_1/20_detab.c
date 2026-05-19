#include <stdio.h>

#define MAXLINE 100
const int TABPOS = 8

int get_line(char line[], int lim);
void detab(char line[], int len, int lim);
int shift(char line[], int len, int pos, int qty, int lim);

int main(void)
{
    int len;

    while ((len = get_line(line, MAXLINE)) > 0) {
        detab(line, len, MAXLINE);
}

int get_line(char line[], int lim)
{
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    line[i] = '\0';

    if (i == lim) {
        while ((c = getline()) != EOF && c != '\n') {
            ;
        }
    }

    return i;
}

void detab(char line[], int len, int lim)
{
    for (int i = 0; i < len; ++i) {
        if (line[i] == '\t') {
            int spaces = TABPOS - (i % TABPOS);

            if (spaces == TABPOS) {
                // Tab sits exactly on a boundary: just delete it
                shift(line, len, i, -1, lim);
                len--;
                i--;
            } else {
                int qty = spaces - 1;
                if (shift(line, len, i, qty, lim) == 0) {
                    for (int j = i; j < i + spaces; ++j)
                        line[j] = ' ';
                    len += qty;
                    i   += spaces - 1;
                }
            }
        }
    }
}

int shift(char line[], int len, int pos, int qty, int lim)
{
    if (pos < 0 || pos >= len || len + qty >= lim || len + qty < 0)
        return 1;

    if (qty > 0) {
        // Shift right: copy backwards to avoid overwriting
        for (int i = len - 1; i >= pos; i--)
            line[i + qty] = line[i];
    } else {
        // Shift left: copy forwards
        for (int i = pos; i < len; i++)
            line[i + qty] = line[i];
    }

    line[len + qty] = '\0';
    return 0;
}
