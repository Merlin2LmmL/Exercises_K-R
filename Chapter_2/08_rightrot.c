#include <stdio.h>

int get_line(char line[], int lim);
unsigned rightrot(unsigned x, int p, int n);
unsigned reverse(unsigned x, int n);
unsigned getbit(unsigned x, int p);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned strtoany(char str[], int b, char charset[], int len);

char BINARY[]  = "01";
char DECIMAL[] = "0123456789";

#define MAXLINE 80
#define INVALID -1

#define TRUE  1
#define FALSE 0

int main(void)
{
    int len, p, n;
    char line[MAXLINE];
    unsigned x;

    len = 1;
    p = n = x = INVALID;

    while (len > 0) {
        if (x == INVALID) {
            printf("Please enter a desired value for x in binary:\n");
            len = get_line(line, MAXLINE);
            x = strtoany(line, 2, BINARY, len);
            continue;
        }

        if (p == INVALID) {
            printf("Please enter a desired value for p in decimal:\n");
            len = get_line(line, MAXLINE);
            p = (int)strtoany(line, 10, DECIMAL, len);
            continue;
        }

        if (n == INVALID) {
            printf("Please enter a desired value for n in decimal:\n");
            len = get_line(line, MAXLINE);
            n = (int)strtoany(line, 10, DECIMAL, len);
            continue;
        }

        if ((x != INVALID) && (p != INVALID) && (n != INVALID)) {
            printf("%b\n", rightrot(x, p, n));
            x = p = n = INVALID;
        }
    }

    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
        line[i] = c;
    }

    line[i] = '\0';

    return i;
}


unsigned rightrot(unsigned x, int p, int n)
{
    unsigned tmp = x & ((~(~0 << n) << (p + 1 - n)));
    tmp = reverse((tmp >>= p + 1 - n), n);
    x = setbits(x, p + 1, n, tmp);
    return x;
}

unsigned reverse(unsigned x, int n)
{
    char tmp;

    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        tmp = getbit(x, i);
        x = setbits(x, i + 1, 1, getbit(x, j));
        x = setbits(x, j + 1, 1, tmp);
    }

    return x;
}

unsigned getbit(unsigned x, int p)
{
    return (x >> p) & ~(~0 << 1);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    x &= ~(~(~0 << n) << ((p - n)));
    y &= ~(~0 << n);
    y <<= (p - n);

    return x |= y;
}

unsigned strtoany(char str[], int b, char charset[], int len)
{
    unsigned value = 0;

    for (int i = 0; i < len; ++i) {
        int found = FALSE;
        for (int j = 0; j < b; ++j) {
            if (str[i] == charset[j]) {
                value *= b;
                value += j;
                found = TRUE;
            }
        }
        if (!found) {
            printf("Invalid base %d value!\n", b);
            return INVALID;
        }
    }

    return value;
}
