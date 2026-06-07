#include <stdio.h>

int main(void)
{
	int c, space_cnt;

	while ((c = getchar()) != EOF) {
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

	return 0;
}
