#include <stdio.h>
#define MAXLINE 100
#define NORMAL       0
#define COMMENT      1
#define STRING       2
#define LITERAL      3
#define LINE_COMMENT 4

int get_line(char line[], int lim);
int remove_comments(char line[], int len);

int main(void)
{
    char line[MAXLINE];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0) {
        len = remove_comments(line, len);
        printf("%s\n", line);
    }
    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
        line[i] = c;
    line[i] = '\0';
    if (i == lim - 1)
        while ((c = getchar()) != '\n' && c != EOF)
            ++i;
    return i;
}

int remove_comments(char line[], int len)
{
    static int state = NORMAL;  /* static: persists across calls for block comments */
    char last_char = '\0';
    int write = 0;

    for (int i = 0; i < len; ++i) {
        char c = line[i];
        if (c == '/' && line[i+1] == '*' && state == NORMAL) {
            state = COMMENT;
            ++i;                        /* skip the '*' */
        } else if (c == '*' && line[i+1] == '/' && state == COMMENT) {
            state = NORMAL;
            ++i;                        /* skip the '/' */
        } else if (c == '/' && line[i+1] == '/' && state == NORMAL) {
            state = LINE_COMMENT;
        } else if (c == '"' && last_char != '\\' && (state == NORMAL || state == STRING)) {
            if (state == NORMAL) state = STRING; else state = NORMAL;
            line[write++] = c;
        } else if (c == '\'' && last_char != '\\' && (state == NORMAL || state == LITERAL)) {
            if (state == NORMAL) state = LITERAL; else state = NORMAL;
            line[write++] = c;
        } else if (state == NORMAL || state == STRING || state == LITERAL) {
            line[write++] = c;
        }
        last_char = c;
    }
    if (state == LINE_COMMENT)
        state = NORMAL;         /* line comments don't survive the newline */
    line[write] = '\0';
    return write;
}
