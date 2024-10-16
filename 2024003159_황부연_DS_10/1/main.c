#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} node;

int main(void)
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		printf("file open error\n");
		return 1;
	}

	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;

	int n;

	fscanf(f, "%d", &n);

	printf("/* MAX_SIZE of a set S : %d */\n", MAX_SIZE);
	printf("current size of S : %d\n", n);

	printf("S = { ");
	int i;
	for (i = 0; i < n - 1; i++)
	{
		printf("%d, ", i);
	}
	printf("%d }", i);

	for (int i = 0; i < n; i++)
	{
		out[i] = 1;
		seq[i] = NULL;
	}

	printf("input pairs : ");

	int a, b;
	while (!feof(f))
	{
		fscanf(f, "%d %d", &a, &b);

		printf("%dR%d ", a, b);

		nodePointer x;
		x = (nodePointer)malloc(sizeof(node));

		x->data = b;
		x->link = seq[a];
		seq[a] = x;

		x = (nodePointer)malloc(sizeof(node));

		x->data = a;
		x->link = seq[b];
		seq[b] = x;
	}

	printf("\n");

	// symmetric relations print

	printf("\nSymmetric 관계 linked List\n");

	for (int i = 0; i < n; i++)
	{
		x = seq[i];
		printf("%d : symmteric 관계:\n", i);

		while (x)
		{
			printf("(%p %d %p)   ", x, x->data, x->link);
			x = x->link;
		}

		printf("\n");
	}

	int j;

	for (int i = 0; i < n; i++)
	{
		if (out[i])
		{
			printf("\nNew class: %5d", i);
			out[i] = 0;
			x = seq[i];
			top = NULL;

			while (1)
			{
				while (x)
				{
					j = x->data;
					if (out[j])
					{
						printf("%5d", j);
						out[j] = 0;

						y = x->link;
						x->link = top;
						top = x;
						x = y;
					}
					else
					{
						x = x->link;
					}
				}

				if (!top) break;
				x = seq[top->data];
				top = top->link;
			}
		}
	}

	printf("\n");

	fclose(f);

	return 0;
}