#include <stdio.h>

#define NUM_DIGITS 10
#define NUM_LETTERS 26

typedef struct {
    int spaces;
    int tabs;
    int newlines;
    int total;
} CharStats;

/* Function declarations */
void countCharacters(FILE *fp, CharStats *stats);
int findLargestGroup(const CharStats *stats);
void displayDiagram(const CharStats *stats);
void printBar(const char *label, int value, int largest, int width, int total);

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

    CharStats stats = {0};

    countCharacters(fp, &stats);
    fclose(fp);

    displayDiagram(&stats);

    return 0;
}

void countCharacters(FILE *fp, CharStats *stats)
{
    int c;
    int consecutive_spaces = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (c == ' ') {
            consecutive_spaces++;
            if (consecutive_spaces == 4) {
                stats->tabs++;
                consecutive_spaces = 0;
                stats->total++;
            }
            continue;
        }

        /* Flush remaining spaces */
        stats->spaces += consecutive_spaces;
        consecutive_spaces = 0;

        if (c == '\n') {
            stats->newlines++;
            stats->total++;
        } else if (c == '\t') {
            stats->tabs++;
            stats->total++;
        }
    }

    /* Flush trailing spaces at EOF */
    stats->spaces += consecutive_spaces;
    stats->total++;
}

int findLargestGroup(const CharStats *stats)
{
    int largest = 0;

    int base_groups[] = {
        stats->spaces,
        stats->tabs,
        stats->newlines,
    };

    for (int i = 0; i < 4; ++i) {
        if (base_groups[i] > largest) {
            largest = base_groups[i];
        }
    }

    return largest;
}

void displayDiagram(const CharStats *stats)
{
    int largest = findLargestGroup(stats);
    const int FULL_BAR_LENGTH = 64;

    if (largest == 0) {
        printf("Nothing to show. Text was empty.\n");
        return;
    }

    printf("================ Newspace Usage ================\n");
    printf("Total Newspaces: %d\n\n", stats->total);

    printBar("Spaces", stats->spaces, largest, FULL_BAR_LENGTH, stats->total);
    printBar("Tabs", stats->tabs, largest, FULL_BAR_LENGTH, stats->total);
    printBar("Newlines", stats->newlines, largest, FULL_BAR_LENGTH, stats->total);
}

/*
 * Print a single bar
 */
void printBar(const char *label, int value, int largest, int width, int total)
{
    int bar_len = (value * width) / largest;
    int percent = (total > 0) ? (value * 100) / total : 0;

    printf("%-12s %6d %3d%% | ", label, value, percent);

    for (int i = 0; i < bar_len; ++i) {
        putchar('#');
    }

    putchar('\n');
}
