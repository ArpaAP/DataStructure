#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

int call_count = 0;
int n;

void print_list(int list[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%4d", list[i]);
    }
    printf("\n");
}

void quick_sort(int list[], int left, int right)
{
	if (left < right)
	{
		call_count++;

		int pivot = left;
		int low = left + 1;
		int high = right;
		int temp;

		printf("pivot = %2d : ", list[pivot]);

		while (low <= high)
		{
			while (list[low] <= list[pivot])
			{
				low++;
			}
			while (list[high] > list[pivot])
			{
				high--;
			}
			if (low <= high)
			{
				SWAP(list[low], list[high], temp);
			}
		}
		SWAP(list[pivot], list[high], temp);

		print_list(list, n);

		quick_sort(list, left, high - 1);
		quick_sort(list, high + 1, right);
	}
}

int main() {
    FILE* f = fopen("input.txt", "r");

    fscanf(f, "%d", &n);

    int* list = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &list[i]);
    }

    printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	print_list(list, n);

	printf("\nexecution of quick sort...\n");
	quick_sort(list, 0, n - 1);

	printf("\ncalls of quick sort: %d\n\n", call_count);

	printf("<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	print_list(list, n);

	fclose(f);
	free(list);

    return 0;
}