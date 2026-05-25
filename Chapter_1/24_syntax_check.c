#include <stdio.h>

#define MAXLINE 100

#define NORMAL       0
#define COMMENT      1
#define STRING       2
#define LITERAL      3
#define LINE_COMMENT 4

int get_line(char line[], int lim);
int remove_comments(char line[], int len);
int count_symbol(char line[], char symbol, int len);

int main(void)
{
    char line[MAXLINE];
    int len;

    int n_parens[2]   = {0, 0};
    int n_brackets[2] = {0, 0};
    int n_braces[2]   = {0, 0};

    int n_strings  = 0;
    int n_literals = 0;

    while ((len = get_line(line, MAXLINE)) >= 0) {
        len = remove_comments(line, len);

        n_parens[0]   += count_symbol(line, '(', len);
        n_parens[1]   += count_symbol(line, ')', len);
        n_brackets[0] += count_symbol(line, '[', len);
        n_brackets[1] += count_symbol(line, ']', len);
        n_braces[0]   += count_symbol(line, '{', len);
        n_braces[1]   += count_symbol(line, '}', len);

        n_strings     += count_symbol(line, '"', len);
        n_literals    += count_symbol(line, '\'', len);
    }

    printf("Parentheses:\nAmount of '(':\t%d\nAmount of ')':\t%d\nDifference:\t%d\n\n", n_parens[0], n_parens[1], n_parens[0] - n_parens[1]);
    printf("Brackets:\nAmount of '[':\t%d\nAmount of ']':\t%d\nDifference:\t%d\n\n", n_brackets[0], n_brackets[1], n_brackets[0] - n_brackets[1]);
    printf("Braces:\nAmount of '{':\t%d\nAmount of '}':\t%d\nDifference:\t%d\n\n", n_braces[0], n_braces[1], n_braces[0] - n_braces[1]);
    printf("Strings:\nAmount of '\"':\t%d\nMod 2:\t\t%d\n\n", n_strings, n_strings % 2);
    printf("Literals:\nAmount of '\\'':\t%d\nMod 2:\t\t%d\n\n", n_literals, n_literals % 2);

    printf("\nSummary:\n");
    if ((n_parens[0] - n_parens[1]) == 0
            && (n_brackets[0] - n_brackets[1]) == 0
            && (n_braces[0] - n_braces[1]) == 0
            && (n_strings % 2) == 0
            && (n_literals % 2) == 0) {
        printf("No rudimentary, obvious syntax errors found. Good Job!\n");
    } else {
        if ((n_parens[0] - n_parens[1]) != 0)       printf(" - Unbalanced amount of Parentheses!\n");
        if ((n_brackets[0] - n_brackets[1]) != 0)   printf(" - Unbalanced amount of Brackets!\n");
        if ((n_braces[0] - n_braces[1]) != 0)       printf(" - Unbalanced amount of Braces!\n");
        if ((n_strings % 2) != 0)                   printf(" - Unbalanced amount of Strings!\n");
        if ((n_literals % 2) != 0)                  printf(" - Unbalanced amount of Literals!\n");

        printf("\nKeep trying!\n");
    }

    return 0;
}

int get_line(char line[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        line[i] = c;
    line[i] = '\0';
    if (i == lim - 1) while ((c = getchar()) != EOF && c != '\n') ++i;

    if (c == EOF && i == 0) return EOF; /* Only exit when EOF is hit */
    return i;
}

int remove_comments(char line[], int len)
{
    static int state = NORMAL;
    char last_char = '\0';
    int write = 0;

    for (int i = 0; i < len; ++i) {
        char c = line[i];

        if (i + 1 < len &&
            c == '/' && line[i+1] == '*' &&
            state == NORMAL) {

            state = COMMENT;
            ++i;

        } else if (i + 1 < len &&
                   c == '*' && line[i+1] == '/' &&
                   state == COMMENT) {

            state = NORMAL;
            ++i;

        } else if (i + 1 < len &&
                   c == '/' && line[i+1] == '/' &&
                   state == NORMAL) {

            state = LINE_COMMENT;

        } else if (c == '"' &&
                   last_char != '\\' &&
                   (state == NORMAL || state == STRING)) {

            state = (state == NORMAL) ? STRING : NORMAL;
            line[write++] = c;

        } else if (c == '\'' &&
                   last_char != '\\' &&
                   (state == NORMAL || state == LITERAL)) {

            state = (state == NORMAL) ? LITERAL : NORMAL;
            line[write++] = c;

        } else if (state == NORMAL ||
                   state == STRING ||
                   state == LITERAL) {

            line[write++] = c;
        }

        last_char = c;
    }

    if (state == LINE_COMMENT)
        state = NORMAL;

    line[write] = '\0';
    return write;
}

int count_symbol(char line[], char symbol, int len)
{
    int n = 0;
    int last_c = '\0';

    for (int i = 0; i < len; ++i) {
        if (line[i] == symbol && last_c != '\\')
            ++n;

        last_c = line[i];
    }

    return n;
}
