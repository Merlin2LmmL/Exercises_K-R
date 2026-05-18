#include <stdio.h>

#define IN  1
#define OUT 0

#define MAXWORD 20
#define MAXBAR  64

unsigned int lengths[MAXWORD + 1];

/* Function declarations */
int count_len(FILE *fp, int *lengths, int lim);
int find_largest_freq(int *lengths, int lim);
void display_diagram(int *lengths, int lim, int bar_len, int total);
void print_bar(const char *label, int value, int largest, int width, int total);

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

    int total = count_len(fp, lengths, MAXWORD);
    fclose(fp);

    display_diagram(lengths, MAXWORD, MAXBAR, total);

    return 0;
}

/*
 * Count word lengths
 * Returns total number of words
 */
int count_len(FILE *fp, int *lengths, int lim)
{
    int c, state = OUT, run = 0;
    int total = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == IN) {
                if (run > lim) {
                    lengths[lim]++;
                } else {
                    lengths[run]++;
                }
                total++;
                run = 0;
            }
            state = OUT;
        } else {
            state = IN;
            run++;
        }
    }

    if (state == IN) {
        if (run > lim) {
            lengths[lim]++;
        } else {
            lengths[run]++;
        }
        total++;
    }

    return total;
}

/*
 * Find largest bucket value
 */
int find_largest_freq(int *lengths, int lim)
{
    int largest = 0;

    for (int i = 0; i <= lim; ++i) {
        if (lengths[i] > largest) {
            largest = lengths[i];
        }
    }

    return largest;
}

/*
 * Display histogram
 */
void display_diagram(int *lengths, int lim, int bar_len, int total)
{
    int largest = find_largest_freq(lengths, lim);

    if (largest == 0) {
        printf("Nothing to show. Text was empty.\n");
        return;
    }

    printf("================ Word Length Histogram ================\n");
    printf("Total Words: %d\n\n", total);

    for (int i = 1; i < lim; ++i) {
        char label[16];
        snprintf(label, sizeof(label), "%d letters", i);
        print_bar(label, lengths[i], largest, bar_len, total);
    }

    print_bar("< max", lengths[lim], largest, bar_len, total);
}

/*
 * Print a single bar
 */
void print_bar(const char *label, int value, int largest, int width, int total)
{
    int bar_len = (value * width) / largest;
    int percent = (total > 0) ? (value * 100) / total : 0;

    printf("%-12s %6d %3d%% | ", label, value, percent);

    for (int i = 0; i < bar_len; ++i) {
        putchar('#');
    }

    putchar('\n');
}
