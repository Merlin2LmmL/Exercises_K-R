#include <stdbool.h>
#include <stdio.h>

int convert(int c);

int start = 0;
int end = 50;
bool reverse = true;
int step = 5;

int main(void)
{
    printf("Celsius\t\tFahrenheit\n");

    int c;

    // Either move from start to end or from end to start depending on reverse.
    for (reverse ? (c = end) : (c = start); reverse ? (c >= start) : (c <= end); reverse ? (c -= step) : (c += step)) {
        printf("%3d\t\t%10d\n", c, convert(c));
    }

    return 0;
}

int convert(int c) {
    return (c * 9 / 5) + 32;
}
