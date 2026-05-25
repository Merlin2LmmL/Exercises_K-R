#include <stdio.h>
#include <limits.h>

int main(void)
{
    unsigned long fib[] = {0, 1, 1};

    printf("%lu\n%lu\n", fib[0], fib[1]);
    while (fib[0] <= ULONG_MAX - fib[1]) {
        printf("%lu\n", (fib[2] = fib[0] + fib[1]));

        fib[0] = fib[1];
        fib[1] = fib[2];
    }

    printf("\n");
    return 0;
}
