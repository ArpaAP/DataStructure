#include "selectionSort.h"
#define SWAP(x, y, temp) ((temp)=(x), (x)=(y), (y)=(temp))

void sort(int a[], int n) {
    int tmp, minIndex;

    for (int i = 0; i < n - 1; i++) {
        minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }

        if (i != minIndex) {
            SWAP(a[i], a[minIndex], tmp);
        }
    }
}
