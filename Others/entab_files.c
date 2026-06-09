#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1024
#define TABSIZE 4

int get_line(FILE *fp, char line[], int lim);
void entab(char line[]);

int main(int argc, char *argv[])
{
	FILE *in, *out;
	char line[MAXLINE];
	char tmpname[1024];

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return 1;
	}

	in = fopen(argv[1], "r");
	if (!in) {
		perror("fopen");
		return 1;
	}

	snprintf(tmpname, sizeof(tmpname), "%s.tmp", argv[1]);

	out = fopen(tmpname, "w");
	if (!out) {
		perror("fopen tmp");
		fclose(in);
		return 1;
	}

	while (get_line(in, line, MAXLINE) > 0) {
		entab(line);
		fputs(line, out);
	}

	fclose(in);
	fclose(out);

	if (remove(argv[1]) != 0) {
		perror("remove");
		return 1;
	}

	if (rename(tmpname, argv[1]) != 0) {
		perror("rename");
		return 1;
	}

	return 0;
}

int get_line(FILE *fp, char line[], int lim)
{
	int c, i;

	for (i = 0;
		 i < lim - 1 &&
		 (c = fgetc(fp)) != EOF &&
		 c != '\n';
		 ++i)
	{
		line[i] = c;
	}

	if (c == '\n')
		line[i++] = c;

	line[i] = '\0';

	return i;
}

/* Modified: Changes 4 space chars at the start of TABPOS to a tab char */
void entab(char line[])
{
	char out[MAXLINE];
	int i = 0, j = 0;
	int spaces = 0;

	while (line[i] == ' ') {
		spaces++;
		i++;
	}

	while (spaces >= TABSIZE) {
		out[j++] = '\t';
		spaces -= TABSIZE;
	}

	while (spaces-- > 0) {
		out[j++] = ' ';
	}

	while (line[i] != '\0') {
		out[j++] = line[i++];
	}

	out[j] = '\0';

	for (i = 0; (line[i] = out[i]) != '\0'; i++);
}
