#include <stdio.h>

#define THRESHOLD 80

int get_line(char line[], int lim);
void print_line(char line[], int lim);

int main(void)
{
    char line[THRESHOLD + 1];

    while (get_line(line, THRESHOLD + 1) > 0) {
        ;
    }

    printf("\n");
    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;

    // Fill Buffer till THRESHOLD
    for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }

    // If THRESHOLD reached, print buffer and print remaining input
    if (i == lim) {
        print_line(line, lim);

        for (; (c = getchar()) != EOF && c != '\n'; ++i) {
            putchar(c);
        }

        printf("\n");
    }

    return i;
}

void print_line(char line[], int lim)
{
    for (int i = 0; i < lim; ++i) {
        putchar(line[i]);
    }
}
