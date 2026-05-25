#include <stdio.h>

#define MAXLINE 100
#define TABPOS 8

int get_line(char line[], int lim);
void entab(char line[], int len, int lim);
int shift(char line[], int pos, int qty, int len, int lim);

int main(void)
{
    char line[MAXLINE];
    int len;

    while ((len = get_line(line, MAXLINE)) > 0) {
        entab(line, len, MAXLINE);
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
            ++i;
        }
    }

    return i;
}

void entab(char line[], int len, int lim)
{
    int space_run = 0;
    int col = 0;                          // display column, independent of i
    for (int i = 0; i < len; ++i) {
        ++col;
        if (line[i] == ' ') {
            ++space_run;
            if (col % TABPOS == 0) {      // use col, NOT (i+1)
                len = shift(line, i - (space_run - 1), -(space_run - 1), len, lim);
                line[i - (space_run - 1)] = '\t';
                i -= (space_run - 1);
                space_run = 0;
                // col is already correct: it's at a tab stop, no adjustment needed
            }
        } else {
            space_run = 0;
        }
    }
}

int shift(char line[], int pos, int qty, int len, int lim)
{
    if (qty > 0)
        return len;
    for (int i = 0; i < -qty; ++i) {
        if (len > lim)
            return len;
        int j;
        for (j = pos + 1; j < len; ++j)
            line[j] = line[j + 1];
        line[j - 1] = '\0';   // ← fix 1a  (j == len here)
        --len;                 // ← fix 1b
    }
    return len;
}
