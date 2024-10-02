#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x, y, tmp) ((tmp)=(x), (x)=(y), (y)=(tmp))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

void selection_sort(int arr[], int n) {
    int i, j, min_idx, tmp;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;

        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (i != min_idx) {
            SWAP(arr[i], arr[min_idx], tmp);
        }
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%5d", arr[i]);
    }
}

int binsearch_recur(int arr[], int search, int left, int right) {
    printf("call binsearch_recur, left=%d, right=%d\n", left, right);

    int middle;

    if (left <= right) {
        middle = (left + right) / 2;

        switch (COMPARE(arr[middle], search)) {
        case -1: return binsearch_recur(arr, search, middle + 1, right);
        case 0: return middle;
        case 1: return binsearch_recur(arr, search, left, middle - 1);
        }
    }

    return -1;
}

int main(void) {
    srand((unsigned int)time(NULL));

    int n;

    printf("Enter the number of numbers to generate: ");
    scanf("%d", &n);

    int arr[100];

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    print_array(arr, n);

    selection_sort(arr, n);

    printf("\n\nSorted array:\n");
    print_array(arr, n);

    printf("\n\nEnter the number to search: ");
    int search;

    scanf("%d", &search);

    int idx = binsearch_recur(arr, search, 0, n + 1);

    if (idx == -1) {
        printf("The search number has not found in arr\n");
    }
    else {
        printf("The search number is present in arr[%d]\n", idx);
    }
}
