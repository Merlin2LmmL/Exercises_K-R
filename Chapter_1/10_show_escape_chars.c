#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    int c, space_cnt;

    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ') {
            ++space_cnt;
        } else {
            space_cnt = 0;
        }
        if (c == '\n') {
            printf("\\n\n");
        }
        else if (c == '\t' || space_cnt >= 4) {
            printf("\\t");
            space_cnt = 0;
        } else if (c == '\b') {
            printf("\\b");
        } else {
            printf("%c", c);
        }
    }

    printf("EOF\n");

    fclose(fp);
    return 0;
}
