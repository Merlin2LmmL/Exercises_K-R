#include <stdio.h>

int main(void)
{
    int cnt, c;
    cnt = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        ++cnt;
    }

    printf("Input was %d chars long\n", cnt);

    return 0;
}
