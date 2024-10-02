#include <stdio.h>
#include <time.h>
#include "selectionSort.h"
#define MAX_SIZE 2001

int main(void) {
    FILE* f;

    if (fopen_s(&f, "out.txt", "w") != 0) {
        printf("error on opening file\n");
        return 1;
    }

    int step = 10;
    int a[MAX_SIZE];
    double duration;
    clock_t start;

    fprintf(f, "      n\ttime\n");

    for (int n = 0; n <= 2000; n += step) {
        for (int i = 0; i < n; i++) {
            a[i] = n - i;
        }

        start = clock();
        sort(a, n);
        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;

        fprintf(f, "%6d\t%f\n", n, duration);
        if (n == 100) step = 100;
    }

    fclose(f);

    return 0;
}
