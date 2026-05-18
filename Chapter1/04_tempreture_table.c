#include <stdbool.h>
#include <stdio.h>

int start = 0;
int end = 50;
bool reverse = true;
int step = 5;

int main(void)
{
    printf("Celsius\t\tFahrenheit\n");

    for (int c = start; c <= end; c += step) {
        int val = reverse ? end - (c - start) : c;
        printf("%3d\t\t%10d\n", val, (val * 9 / 5) + 32);
    }

    return 0;
}
