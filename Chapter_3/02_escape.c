#include <stdio.h>

int escape(char s[], char t[], int len, int lim);
int rev_escape(char s[], char t[], int len);
int get_line(char line[], int lim);
void scopy(char s[], char t[], int len);

#define MAXLINE 80
#define TABPOS  8

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = get_line(line, MAXLINE)) != 0) {
        char tmp[MAXLINE];
        len = escape(line, tmp, len, MAXLINE);

        scopy(tmp, line, len);

        len = rev_escape(line, tmp, len);

        scopy(tmp, line, len);

        /*
         * Currently we are showing and then reversing escape chars,
         * which will resort in identical output to its input.
         */
        printf("%s", line);
    }

    printf("\n");
    return 0;
}

int escape(char s[], char t[], int len, int lim)
{
    int j, i;
    for (i = j = 0; i < len; ++i, ++j) {
        switch (s[i]) {
        case '\n':
            if ((j + 1) < lim) {
                t[j] = '\\';
                t[++j] = 'n';
            } else {
                t[j++] = '\0';
                return j;
            }
            break;
        case '\t':
            if ((j + 1) < lim) {
                t[j] = '\\';
                t[++j] = 't';
            } else {
                t[j++] = '\0';
                return j;
            }
            break;
        case EOF: /* We're printing EOF at the end of the for loop anyway */
        default:
            t[j] = s[i];
            break;
        }
    }

    t[j++] = '\0';
    return j;
}

int rev_escape(char s[], char t[], int len)
{
    int j, c_prev;
    c_prev = '\0';

    for (int i = j = 0; i < len; ++i, ++j) {
        switch (s[i]) {
        case 'n':
            if (c_prev == '\\')
                t[j-- - 1] = '\n';
            break;
        case 't':
            if (c_prev == '\\')
                t[j-- - 1] = '\t';
            break;
        default:
            t[j] = s[i];
            break;
        }
        c_prev = s[i];
    }

    return j;
}

int get_line(char line[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }

    if (c == '\n')
        line[i++] = c;

    line[i] = '\0';

    if (i >= lim) {
        while ((c = getchar()) != EOF) {
            ++i;
        }
    }

    return i;
}

/* Safely copy by clearing the source afterwards */
void scopy(char s[], char t[], int len)
{
    for (int i = 0; i < len; ++i) {
        t[i] = s[i];
        s[i] = '\0';
    }
}
