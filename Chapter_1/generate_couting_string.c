#include <stdio.h>

#define MAXLINE 5

int convert_to_int(char s[]);
int get_line(char line[], int lim);

int main(void)
{
    char line[MAXLINE];
    int num;

    printf("Enter the number you would like to count to.\n");

    get_line(line, MAXLINE);
    if ((num = convert_to_int(line)) < 0) {
        printf("Please enter a valid max %d digit number.\n", MAXLINE - 1);
        return 1;
    }

    for (int i = 0; i <= num; ++i) {
        printf("%d ", i);
    }

    printf("\n");
    return 0;
}

int get_line(char line[], int lim)
{
    int i, c;

    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
        line[i] = c;
    }

    line[i] = '\0';

    return i;
}

int convert_to_int(char s[])
{
    int num = 0;

    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] >= '0' && s[i] <= '9') {
            num = num * 10 + (s[i] - '0');
        } else return -1;
    }

    return num;
}
