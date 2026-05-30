#include <stdio.h>
#include <limits.h>

int main(void)
{
    printf("Range of the signed short:\t%d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("Range of the unsigned short:\t0 to %u\n", USHRT_MAX);

    printf("Range of the signed int:\t%d to %d\n", INT_MIN, INT_MAX);
    printf("Range of the unsigned int:\t0 to %u\n", UINT_MAX);

    printf("Range of the signed long:\t%ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("Range of the unsigned long:\t0 to %lu\n", ULONG_MAX);

    printf("Range of the signed char:\t%d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("Range of the unsigned char:\t0 to %u\n", UCHAR_MAX);

    return 0;
}
