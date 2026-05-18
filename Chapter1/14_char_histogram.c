#include <stdio.h>

#define NUM_DIGITS 10
#define NUM_LETTERS 26

typedef struct {
    int spaces;
    int tabs;
    int newlines;
    int other;
    int total;
    int numbers[NUM_DIGITS];
    int letters[NUM_LETTERS];
} CharStats;

/* Function declarations */
void count_chars(FILE *fp, CharStats *stats);
int find_largest(const CharStats *stats);
void display_diagram(const CharStats *stats);
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

    CharStats stats = {0};

    count_chars(fp, &stats);
    fclose(fp);

    display_diagram(&stats);

    return 0;
}

void count_chars(FILE *fp, CharStats *stats)
{
    int c;
    int space_run = 0;

    while ((c = fgetc(fp)) != EOF) {
        stats->total++;

        if (c == ' ') {
            space_run++;
            if (space_run == 4) {
                stats->tabs++;
                space_run = 0;
            }
            continue;
        }

        /* Flush remaining spaces */
        stats->spaces += space_run;
        space_run = 0;

        if (c == '\n') {
            stats->newlines++;
        } else if (c == '\t') {
            stats->tabs++;
        } else if (c >= '0' && c <= '9') {
            stats->numbers[c - '0']++;
        } else if (c >= 'A' && c <= 'Z') {
            stats->letters[c - 'A']++;
        } else if (c >= 'a' && c <= 'z') {
            stats->letters[c - 'a']++;
        } else {
            stats->other++;
        }
    }

    /* Flush trailing spaces at EOF */
    stats->spaces += space_run;
}

int find_largest(const CharStats *stats)
{
    int largest = 0;

    int base_groups[] = {
        stats->spaces,
        stats->tabs,
        stats->newlines,
        stats->other
    };

    for (int i = 0; i < 4; ++i) {
        if (base_groups[i] > largest) {
            largest = base_groups[i];
        }
    }

    for (int i = 0; i < NUM_DIGITS; ++i) {
        if (stats->numbers[i] > largest) {
            largest = stats->numbers[i];
        }
    }

    for (int i = 0; i < NUM_LETTERS; ++i) {
        if (stats->letters[i] > largest) {
            largest = stats->letters[i];
        }
    }

    return largest;
}

void display_diagram(const CharStats *stats)
{
    int largest = find_largest(stats);
    const int FULL_BAR_LENGTH = 64;

    if (largest == 0) {
        printf("Nothing to show. Text was empty.\n");
        return;
    }

    printf("================ Character Usage ================\n");
    printf("Total Characters: %d\n\n", stats->total);

    print_bar("Spaces", stats->spaces, largest, FULL_BAR_LENGTH, stats->total);
    print_bar("Tabs", stats->tabs, largest, FULL_BAR_LENGTH, stats->total);
    print_bar("Newlines", stats->newlines, largest, FULL_BAR_LENGTH, stats->total);
    print_bar("Other", stats->other, largest, FULL_BAR_LENGTH, stats->total);

    char label[32];

    for (int i = 0; i < NUM_DIGITS; ++i) {
        snprintf(label, sizeof(label), "Digit %d", i);
        print_bar(label, stats->numbers[i], largest, FULL_BAR_LENGTH, stats->total);
    }

    for (int i = 0; i < NUM_LETTERS; ++i) {
        snprintf(label, sizeof(label), "Letter %c", (char)(i + 'A'));
        print_bar(label, stats->letters[i], largest, FULL_BAR_LENGTH, stats->total);
    }
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
