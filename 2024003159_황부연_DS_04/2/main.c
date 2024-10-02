#include <stdio.h>

#define MAX_TERMS 101
#define MAX_ROW 100
#define MAX_COL 100
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))

typedef struct {
	int row;
	int col;
	int value;
} term;

void fastTranspose(term a[], term b[])
{
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a[0].col, numTerms = a[0].value;

	b[0].row = numCols;
	b[0].col = a[0].row;
	b[0].value = numTerms;

	if (numTerms > 0)
	{
		for (i = 0; i < numCols; i++)
		{
			rowTerms[i] = 0;
		}

		for (i = 1; i <= numTerms; i++)
		{
			rowTerms[a[i].col]++;
		}

		startingPos[0] = 1;

		for (i = 1; i < numCols; i++)
		{
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}

		for (i = 1; i <= numTerms; i++)
		{
			j = startingPos[a[i].col]++;
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}

void printMatrix(term terms[])
{
	int arr[MAX_COL][MAX_ROW] = { 0 };

	for (int i = 1; i <= terms[0].value; i++)
	{
		arr[terms[i].row][terms[i].col] = terms[i].value;
	}

	for (int i = 0; i < terms[0].row; i++)
	{
		for (int j = 0; j < terms[0].col; j++)
		{
			printf("%4d ", arr[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
	FILE *inputFile, *outputFile;

	term a[MAX_TERMS], b[MAX_TERMS];

	fopen_s(&inputFile, "a.txt", "r");

	if (inputFile == NULL)
	{
		printf("error on opening file");
		return 1;
	}

	fscanf_s(inputFile, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);

	for (int i = 1; i <= a[0].value; i++)
	{
		fscanf_s(inputFile, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
	}

	fclose(inputFile);

	printf("A\n");
	printMatrix(a);

	fastTranspose(a, b);

	printf("B\n");
	printMatrix(b);

	fopen_s(&outputFile, "b.txt", "w");

	if (outputFile == NULL)
	{
		printf("error on opening file");
		return 1;
	}

	for (int i = 0; i <= b[0].value; i++)
	{
		fprintf(outputFile, "%d %d %d\n", b[i].row, b[i].col, b[i].value);
	}

	fclose(outputFile);

	return 0;
}