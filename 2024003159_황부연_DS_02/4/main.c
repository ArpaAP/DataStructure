#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "selectionSort.h"
#define MAX_SIZE 2001

int main(void) {
    FILE* f;

    srand((unsigned int)time(NULL));

    if (fopen_s(&f, "out.txt", "w") != 0) {
        printf("error on opening file\n");
        return 1;
    }

    int step = 10;
    int a[MAX_SIZE];
    double duration_reversed, duration, duration_random;

    fprintf(f, "      n\trepetitions\t역정렬\t순정렬\t랜덤\n");

    for (int n = 0; n <= 2000; n += step) {
        long repetitions;
        clock_t start;

        // 역정렬

        repetitions = 0;
        start = clock();

        do {
            repetitions++;

            for (int i = 0; i < n; i++) {
                a[i] = n - i;
            }

            sort(a, n);
        } while (clock() - start < 1000);

        duration_reversed = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        duration_reversed /= repetitions;

        // 순정렬

        repetitions = 0;
        start = clock();

        do {
            repetitions++;

            for (int i = 0; i < n; i++) {
                a[i] = i;
            }

            sort(a, n);
        } while (clock() - start < 1000);

        duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        duration /= repetitions;

        // 랜덤

        repetitions = 0;
        start = clock();

        do {
            repetitions++;

            for (int i = 0; i < n; i++) {
                a[i] = rand() % n;
            }

            sort(a, n);
        } while (clock() - start < 1000);

        duration_random = ((double)(clock() - start)) / CLOCKS_PER_SEC;
        duration_random /= repetitions;

        fprintf(f, "%6d\t%d\t%f\t%f\t%f\n", n, repetitions, duration_reversed, duration, duration_random);
        if (n == 100) step = 100;
    }

    fclose(f);

    return 0;
}
