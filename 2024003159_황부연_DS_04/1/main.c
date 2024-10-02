#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 20
#define COLS 20
#define MAX_TERMS 401

typedef struct {
	int row;
	int col;
	int value;
} term;

int main(void)
{
	srand((unsigned long)time(NULL));
	int n;

	int arr[ROWS][COLS] = { 0 };
	term terms[MAX_TERMS];

	printf("원소의 개수를 쓰시오: ");
	scanf_s("%d", &n);

	for (int i = 0; i < n; i++)
	{
		arr[rand() % ROWS][rand() % COLS] = rand() % 100;
	}

	printf("Random generated Matrix(20, 20)\n");

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			printf("%5d", arr[i][j]);
		}
		printf("\n");
	}

	int count = 0;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (arr[i][j] == 0) continue;

			terms[count].row = i;
			terms[count].col = j;
			terms[count].value = arr[i][j];

			count++;
		}
	}

	printf("sparce matrix\n");
	printf("%5d%5d%5d\n", ROWS, COLS, n);

	for (int i = 0; i < count; i++)
	{
		printf("%5d%5d%5d\n", terms[i].row, terms[i].col, terms[i].value);
	}
}