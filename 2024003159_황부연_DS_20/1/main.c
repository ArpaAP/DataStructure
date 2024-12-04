#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void inc_insertion_sort(int list[], int first, int last, int gap)
{
    int key, j;
    for (int i = first + gap; i <= last; i += gap)
    {
        key = list[i];

        for (j = i - gap; j >= first && key < list[j]; j -= gap)
        {
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}

void print_list(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%5d", list[i]);
    }
    printf("\n");
}

void shell_sort(int list[], int n)
{
    int gap;
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        if (gap % 2 == 0) gap++;
        for (int i = 0; i < gap; i++)
        {
            inc_insertion_sort(list, i, n - 1, gap);
        }

        printf("\ngap is %5d ====>\n", gap);
        print_list(list, n);
    }
}

int main() {
    FILE* f = fopen("input.txt", "r");

    int n;
    fscanf(f, "%d", &n);

    int* list = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &list[i]);
    }

    printf("list[] data\n");
    print_list(list, n);

    shell_sort(list, n);

	fclose(f);
	free(list);

    return 0;
}