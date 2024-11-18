#define _CRT_SECURE_NO_WARNINGS
#define RUNS 8
#define RUN_COUNT 10
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int indices[RUNS] = { 0 };
int runs[RUNS][RUN_COUNT];
int winTree[2 * RUNS - 1];

int getValue(int run) {
    if (indices[run] < RUN_COUNT) {
        return runs[run][indices[run]];
    }
    else {
        return INT_MAX;
    }
}

void initWinTree() {
    for (int i = 0; i < RUNS; i++) {
        winTree[RUNS - 1 + i] = i;
    }

    for (int i = RUNS - 2; i >= 0; i--) {
        int leftChild = winTree[2 * i + 1];
        int rightChild = winTree[2 * i + 2];

        if (getValue(leftChild) <= getValue(rightChild)) {
            winTree[i] = leftChild;
        }
        else {
            winTree[i] = rightChild;
        }
    }
}

void updateWinTree(int run) {
    int leafIdx = RUNS - 1 + run;

    while (leafIdx > 0) {
        int parentIdx = (leafIdx - 1) / 2;
        int siblingIdx = (leafIdx % 2 == 0) ? leafIdx - 1 : leafIdx + 1;

        int leftChild = winTree[parentIdx * 2 + 1];
        int rightChild = winTree[parentIdx * 2 + 2];

        if (getValue(leftChild) <= getValue(rightChild)) {
            winTree[parentIdx] = leftChild;
        }
        else {
            winTree[parentIdx] = rightChild;
        }

        leafIdx = parentIdx;
    }
}

void printRunTop(int run) {
	printf("%d ", runs[run][indices[run]]);
}

int main(void)
{
	FILE* f;
	
	if ((f = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "file open error\n");
        return 1;
	}

    printf("<<<<<<<<<<<< run data >>>>>>>>>>>>>\n\n");

	for (int i = 0; i < RUNS; i++)
	{
        printf("%d-th run:\n", i + 1);
		for (int j = 0; j < RUN_COUNT; j++)
		{
			fscanf(f, "%d", &runs[i][j]);
			printf("%5d", runs[i][j]);
		}
        printf("\n");
	}

    fclose(f);

    for (int i = 0; i < RUNS; i++) {
        indices[i] = 0;
    }

    initWinTree();

    printf("\nLevel-order traversal for initial min-winner tree\n");

	for (int i = 0; i < 2 * RUNS - 1; i++) {
		printf("%d ", getValue(winTree[i]));
	}

    printf("\n\nsorting with min-winner tree...\n");

    printf("\nsorted result\n");

    for (int i = 0; i < RUNS; i++) {
        for (int j = 0; j < RUN_COUNT; j++)
        {
            int winner = winTree[0];
            printf("%4d", getValue(winner));

            indices[winner]++;

            updateWinTree(winner);
        }
		printf("\n");
    }
    printf("\n");

    return 0;
}