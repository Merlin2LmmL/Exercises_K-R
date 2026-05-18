#include <stdio.h>

int main(void)
{
    int c, lastC;

    while ((c = getchar()) != EOF) {

        if (!(c == ' ' && lastC == ' ')) {
            putchar(c);
        }

        lastC = c;
    }
    printf("\n");

    return 0;
}
