#include <stdio.h>
#define MAXLINE 10

int get_line(char line[], int lim);

int main(void)
{
    char line[MAXLINE];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0) {
        printf("%s\n", line);   /* prints the last (or only) segment */
    }
}

int get_line(char line[], int lim)
{
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
        if (i == lim - 2) {             /* buffer full */
            int has_break = 0;
            int j;
            /* find last space/tab in buffer */
            for (j = lim - 2; j >= 0; --j) {
                if (line[j] == ' ' || line[j] == '\t') {
                    has_break = 1;
                    break;
                }
            }
            if (has_break) {
                /* print everything before the space */
                for (int k = 0; k < j; ++k)
                    printf("%c", line[k]);
                printf("\n");
                /* carry the word after the space to the front */
                int carry_len = 0;
                for (int k = j + 1; k <= lim - 2; ++k)
                    line[carry_len++] = line[k];
                /* clear the rest of the buffer */
                for (int k = carry_len; k < lim; ++k)
                    line[k] = '\0';
                i = carry_len - 1; /* -1 because for loop will ++i */
            } else {
                /* no space anywhere: hard break at column limit */
                line[lim - 1] = '\0';
                printf("%s\n", line);
                for (int k = 0; k < lim; ++k)
                    line[k] = '\0';
                i = -1;            /* ++i makes it 0, fresh start */
            }
        }
    }
    line[i] = '\0';
    return i;
}
