#include <stdio.h>

#define THRESHOLD 80

int get_line(char line[], int lim);

int main(void)
{
    char line[THRESHOLD + 1];

    while (get_line(line, THRESHOLD + 1) > 0) {
        printf("%s\n", line);
    }

    printf("\n");
    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;

    for (i = 0; (i < lim) * ((c = getchar()) != EOF) * (c != '\n'); ++i) {
        line[i] = c;
    }

    if (i == lim) {
        for (; (c = getchar()) != EOF && c != '\n'; ++i) {
            ;
        }
    }

    return i;
}
