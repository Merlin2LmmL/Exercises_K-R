#include <stdio.h>

int main(void)
{
    const char *escape_chars[] = {
        "a", "b", "e", "f", "n", "r", "t", "v", "\134",
        "\042", "?", "nnn", "xhh", "uhhhh", "uhhhhhhhh"
    };

    for (int i = 0; i < 15; ++i) {
        printf("%s:\t123.%c.456\n", escape_chars[i], escape_chars[i]);
    }

    return 0;
}
