#include <stdio.h>
#include <stdlib.h>
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

    fprintf(f, "      n\trepetitions\ttime\n");

    for (int n = 0; n <= 2000; n += step) {
        long repetitions = 0;
        clock_t start = clock();

        do {
            repetitions++;

            for (int i = 0; i < n; i++) {
                a[i] = n - i;
            }

            sort(a, n);
        } while (clock() - start < 1000);

        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        duration /= repetitions;

        fprintf(f, "%6d\t%d\t%f\n", n, repetitions, duration);
        if (n == 100) step = 100;
    }

    fclose(f);

    return 0;
}
