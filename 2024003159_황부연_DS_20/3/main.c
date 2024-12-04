#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

int pass_count;

void print_list(int list[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%3d ", list[i]);
	}
	printf("\n");
}

void merge(int list[], int left, int mid, int right, int n) {
	int i = left;
	int j = mid + 1;
	int k = left;
	int l;
	int* sorted = (int*)malloc(sizeof(int) * n);

	while (i <= mid && j <= right) {
		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];
		}
		else {
			sorted[k++] = list[j++];
		}
	}
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];
		}
	}
	for (l = left; l <= right; l++) {
		list[l] = sorted[l];
	}
	
	free(sorted);
}

void merge_pass(int list[], int n, int s) {
	pass_count += 1;
	int i;

	printf("segment size: %d\n", s);

	if (pass_count % 2 == 1) printf("          a : ");
	else printf("       temp : ");
	print_list(list, n);

	for (i = 0; i < n - 2 * s; i += 2 * s) {
		merge(list, i, i + s - 1, i + 2 * s - 1, n);
	}

	if (i + s < n) {
		merge(list, i, i + s - 1, n - 1, n);
	}
	else {
		for (int j = i; j < n; j++) {
			list[j] = list[j];
		}
	}

	if (pass_count % 2 == 0) printf("          a : ");
	else printf("       temp : ");
	print_list(list, n);
	printf("\n");
}

void merge_sort(int list[], int n) {
	int s = 1;

	while (s < n) {
		merge_pass(list, n, s);
		s *= 2;
	}
}

int main()
{
	FILE* f = fopen("input.txt", "r");

	int n;
	fscanf(f, "%d", &n);
	int* list = (int*)malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &list[i]);
	}

	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	print_list(list, n);

	printf("\n<<<<< executing iterative merge sort >>>>>\n");
	merge_sort(list, n);

	printf("\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	print_list(list, n);

	fclose(f);
	free(list);

	return 0;
}