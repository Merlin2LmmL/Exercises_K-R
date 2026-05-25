#include <stdio.h>
#include <limits.h>

int main(void)
{
    for (unsigned long i = 2; i < ULONG_MAX; ++i) {
        unsigned long j;
        for (j = 2; j * j <= i; ++j)
            if (i % j == 0) break;
        if (j * j > i)
            printf("%lu\n", i);
    }

    printf("\n");
    return 0;
}
