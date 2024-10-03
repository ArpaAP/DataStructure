#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

#define MAX_STACK_SIZE 100

typedef struct {
	short int vert;
	short int horiz;
} offsets;

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;

offsets move[8] = {
	{-1, 0}, {-1, 1}, {0, 1}, {1, 1},
	{1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

int rows, cols;
int** maze;
int** mark;

element stack[MAX_STACK_SIZE];
int top;

element pop()
{
	if (top == -1) {
		fprintf(stderr, "Stack is empty\n");
		exit(EXIT_FAILURE);
	}

	return stack[top--];
}

void push(element item)
{
	if (top >= MAX_STACK_SIZE - 1) {
		fprintf(stderr, "Stack is full\n");
		exit(EXIT_FAILURE);
	}

	stack[++top] = item;
}

void path()
{
	int i, row, col, nextRow, nextCol, dir, found = 0;
	mark[1][1] = 1;
	top = 0;
	stack[0].row = 1;
	stack[0].col = 1;
	stack[0].dir = 1;

	while (top > -1 && !found) {
		element position = pop();

		row = position.row;
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;

			if (nextRow == rows && nextCol == cols) {
				found = 1;
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;

				push(position);

				row = nextRow;
				col = nextCol;
				dir = 0;
			}
			else ++dir;
		}
	}

	if (found) {
		printf("The path is:\n");
		printf("row col\n");
		for (i = 0; i <= top; i++) {
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		}
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", rows, cols);
	}
	else {
		printf("The maze does not have a path\n");
	}
}

int main(void)
{
	FILE* f;

	if (!(f = fopen("input.txt", "r"))) {
		fprintf(stderr, "Cannot open the file\n");
		exit(EXIT_FAILURE);
	}
	
	fscanf(f, "%d %d", &rows, &cols);
	
	MALLOC(maze, sizeof(*maze) * (rows + 2));

	for (int i = 0; i < rows + 2; i++) {
		MALLOC(maze[i], sizeof(**maze) * (cols + 2));
	}

	for (int i = 0; i < rows + 2; i++) {
		for (int j = 0; j < cols + 2; j++) {
			maze[i][j] = 1;
		}
	}

	for (int i = 1; i < rows + 1; i++) {
		for (int j = 1; j < cols + 1; j++) {
			fscanf(f, "%d", &maze[i][j]);
		}
	}

	fclose(f);

	MALLOC(mark, sizeof(*mark) * (rows + 2));

	for (int i = 0; i < rows + 2; i++) {
		MALLOC(mark[i], sizeof(**mark) * (cols + 2));
	}

	for (int i = 0; i < rows + 2; i++) {
		for (int j = 0; j < cols + 2; j++) {
			mark[i][j] = 0;
		}
	}

	path();

	for (int i = 0; i < rows + 2; i++) {
		free(maze[i]);
	}

	free(maze);

	for (int i = 0; i < rows + 2; i++) {
		free(mark[i]);
	}

	free(mark);

	return 0;
}