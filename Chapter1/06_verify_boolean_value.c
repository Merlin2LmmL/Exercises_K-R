#include <stdio.h>

/* Try by entering random Gibberish or Pressing Ctl + D to print EOF */

int main(void)
{
    int c;

    while (c = getchar() != EOF) {
        printf("%d\n", c);
    }

    printf("%d\n", c);

    return 0;
}
