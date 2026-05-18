#include <stdbool.h>
#include <stdio.h>

int start = 0;
int end = 50;
bool reverse = true;
int step = 5;

int main(void)
{
    printf("Fahrenheit:\t\tCelcius:\n");

    for (int c = start; c <= end; c += step) {
        int val = reverse ? end - (c - start) : c;
        printf("%3d\t\t%14.2f\n", val, (float) ((val - 32.0) * 5.0 / 9.0));
    }

    return 0;
}
