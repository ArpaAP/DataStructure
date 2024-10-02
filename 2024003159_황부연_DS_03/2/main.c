#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CALLOC(p, n, s)\
	if (!((p) = calloc(n,s))) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE);\
	}

int** make2dArray(int rows, int cols)
{
	int** dp;
	CALLOC(dp, rows, sizeof(int*));

	for (int i = 0; i < rows; i++)
	{
		CALLOC(dp[i], cols, sizeof(int));

		for (int j = 0; j < cols; j++)
		{
			dp[i][j] = rand() % 100;
		}
	}

	return dp;
}

void free2dArray(int** p, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		free(p[i]);
	}
	free(p);
}

int main(void)
{
	int** ipp;
	int rows, cols;

	srand((unsigned int) time(NULL));

	printf("이차원 배열의 행과 열의 수를 입력 하세요 : ");
	scanf_s("%d %d", &rows, &cols);

	ipp = make2dArray(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("ipp[%d][%d] = %d ", i, j, ipp[i][j]);
		}
		printf("\n");
	}

	free2dArray(ipp, rows, cols);

	return 0;
}