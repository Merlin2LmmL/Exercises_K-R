#include <stdio.h>

int binsearch(int x, int v[], int n);
void create_array(int arr[], int size);

#define SIZE   100
#define SEARCH 69

int main(void)
{
    int arr[SIZE];
    create_array(arr, SIZE);

    int result;
    printf("arr[%d] == %d\n", result = binsearch(SEARCH, arr, SIZE - 1), arr[result]);

    if (result == -1)
        return -1;

    return 0;
}

/* Search x in v[0] <= v[1] <= v[2] <= ... <= v[n - 1] */
int binsearch(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;

    while (low < high) {
        /* lowers the chances of an overflow */
        int mid = low + (high - low) / 2;
        if (x > v[mid]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    if (v[low] == x)
        return low;
    else
        return -1;
}

/*
 * Shape this function to your needs. Possibly modify it
 * to set the values to random ones. Only restriction is
 * to have any value be bigger than its previous one.
 */
void create_array(int arr[], int size)
{
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }
}
