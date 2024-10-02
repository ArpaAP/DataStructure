#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CALLOC(p, n, s)\
	if (!((p) = calloc(n,s))) {\
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE);\
	}

int* make1dArray(int num)
{
	int* p;

	CALLOC(p, num, sizeof(int));

	for (int i = 0; i < num; i++)
	{
		p[i] = rand() % 100;
	}

	return p;
}

int main(void)
{
	int* ipp;
	int num;

	srand((unsigned int) time(NULL));

	printf("일차원 배열의 수를 입력하세요: ");
	scanf_s("%d", &num);

	ipp = make1dArray(num);

	for (int i = 0; i < num; i++)
	{
		printf("ipp[%2d] =%2d ", i, ipp[i]);
		
		if ((i % 5) == 4)
		{
			printf("\n");
		}
	}

	free(ipp);

	return 0;
}