#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENTS 200

#include <stdio.h>
#include <stdlib.h>

typedef struct element {
	int key;

} element;

element heap[MAX_ELEMENTS];
int n = 0;

int isHeapFull(int n)
{
	return n == MAX_ELEMENTS - 1;
}

int isHeapEmpty(int n)
{
	return !n;
}

void push(element item, int* n)
{
	int i;
	if (isHeapFull(*n))
	{
		fprintf(stderr, "The heap is full.\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);
	while ((i != 1) && (item.key > heap[i / 2].key))
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

void printHeap()
{
	for (int i = 1; i <= n; i++)
	{
		printf("%3d ", heap[i].key);
	}
	printf("\n");
}

element pop(int* n)
{
	int parent, child;
	element item, temp;
	if (isHeapEmpty(*n))
	{
		fprintf(stderr, "The heap is empty\n");
		exit(EXIT_FAILURE);
	}

	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;

	while (child <= *n)
	{
		if ((child < *n) && (heap[child].key < heap[child + 1].key))
		{
			child++;
		}
		if (temp.key >= heap[child].key) break;

		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}

int main(void)
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "file open error\n");
		exit(EXIT_FAILURE);
	}

	printf("***** insertion into a max heap *****\n");

	element e;
	while (!feof(f))
	{
		fscanf(f, "%d", &e.key);
		push(e, &n);
		printHeap();
	}

	printf("***** deletion from a max heap *****\n");
	for (int i = n; n > 0; i--)
	{
		e = pop(&n);
		printf("delete data = %d\n", e.key);
		printHeap();
	}

	fclose(f);

	return 0;
}