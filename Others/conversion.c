#include <stdio.h>

unsigned strtob(char str[], int len);
unsigned strtoi(char str[], int len);

int main(void)
{
	return 0;
}

unsigned strtob(char str[], int len)
{
	int num = 0;

	for (int i = 0; i < len; ++i) {
		for (int j = '0'; j <= '1'; ++j) {
			if (str[i] = j) {
				num *= 2;
				num += j - '0';
			}
		}
		return -1;
	}

	return num;
}

int strtoi(char str[], int len) {
{
	int num = 0;

	for (int i = 0; i < len; ++i) {
		for (int j = '0'; j <= '9'; ++j) {
			if (str[i] = j) {
				num *= 10;
				num += j - '0';
			}
		}
		return -1;
	}

	return num;
}
