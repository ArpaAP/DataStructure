#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_SIZE 499

int nums[MAX_SIZE + 1] = { 0 };
int sorted[MAX_SIZE + 1] = { 0 };
int winTree[2 * MAX_SIZE] = { NULL };

void winner(int cur, int k, int winTree[])
{
	int i, j, parent, start;

	start = k + k - 1;
	parent = start / 2;

	while (parent >= 1)
	{
		if (winTree[start] > winTree[start - 1])
		{
			winTree[parent] = winTree[start - 1];
		}
		else
		{
			winTree[parent] = winTree[start];
		}

		start = start - 2;
		parent = start / 2;
	}
}

void inorder(int root, int k, int winTree[])
{
	if (root < 2 * k)
	{
		inorder(2 * root, k, winTree);
		printf("%5d", winTree[root]);
		inorder(2 * root + 1, k, winTree);
	}
}

void adjust(int ind, int winTree[])
{
	int i = ind;
	int cmp;

	while (i != 1)
	{
		cmp = i % 2 ? i - 1 : i + 1;
		if (winTree[i] <= winTree[cmp])
		{
			winTree[i / 2] = winTree[i];
		}
		else
		{
			winTree[i / 2] = winTree[cmp];
		}
		i = i / 2;
	}
}

int main(void)
{
	printf("<<<<<<<<<<<<< sortring with winner tree >>>>>>>>>>>>>\n\n");
	unsigned int seed;
	int k;

	printf("the number of keys ( 4, 8, 16, or 32 as a power of 2 )  >> ");
	scanf("%d", &k);

	printf("value of seed >> ");
	scanf("%u", &seed);

	srand(seed);

	for (int i = 1; i <= k; i++)
	{
		nums[i] = (rand() % MAX_SIZE) + 1;
		printf("%5d", nums[i]);
	}
	printf("\n");

	printf("\ninitialization of min-winner tree\n");
	for (int cnt = k, i = 1; i <= k; cnt++, i++)
	{
		winTree[cnt] = nums[i];
	}

	winner(1, k, winTree);
	printf("\ninorder traversal for min-winner tree\n");
	inorder(1, k, winTree);

	for (int i = 1; i <= k; i++)
	{
		sorted[i] = winTree[1];
		if (i != k)
		{
			int j = k;
			for (j = k; j < 2 * k; j++)
			{
				if (sorted[i] == winTree[j])
				{
					winTree[j] = INT_MAX;
					break;
				}
			}
			adjust(j, winTree);
		}

		if (i == 2)
		{
			printf("\nWinner Tree inorder traversal after find 2 winners...\n");
			inorder(1, k, winTree);
		}
	}

	printf("\n\nsorting with min-winner tree...\n");
	printf("sorted result\n");

	for (int i = 1; i <= k; i++)
	{
		printf("%5d", sorted[i]);
	}

	return 0;
}
