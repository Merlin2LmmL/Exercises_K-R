#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    unsigned long n = strtoul(argv[1], NULL, 10);
    unsigned long last_prime = 0;
    for (unsigned long i = 2; i < n; ++i) {
        unsigned long j;
        for (j = 2; j * j <= i; ++j)
            if (i % j == 0) break;
        if (j * j > i)
            last_prime = i;
    }

    printf("%lu\n", last_prime);
    return 0;
}
