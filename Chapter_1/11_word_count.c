#include <stdio.h>

#define IN 1
#define OUT 0
char WS_CHARS[] = {' ', '\t', '\n'};
int WS_CHARS_LEN = sizeof(WS_CHARS) / sizeof(WS_CHARS[0]);

int main(void)
{
    int c, nw, state;
    state = OUT;
    nw = 0;

    while ((c = getchar()) != EOF) {
        for (int i = 0; i < WS_CHARS_LEN; ++i) {
            if (c == WS_CHARS[i]) {
                state = OUT;
            } else if (state == OUT) {
                state = IN;
                ++nw;
            }
        }
    }

    printf("Input has %d words.\n", nw);

    return 0;
}
