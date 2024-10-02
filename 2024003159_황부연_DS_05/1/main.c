#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NAME_SIZE 100
#define MAX_STACK_SIZE 5

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

void sprint()
{
	for (int i = top; i >= 0; i--)
	{
		printf("%d %s\n", stack[i].id, stack[i].name);
	}
	printf("\n\n");
}

int main(void)
{
	FILE* f;

	fopen_s(&f, "input.txt", "r");

	if (f == NULL)
	{
		printf("File open error\n");
		return 1;
	}

	char cmd[100];

	while (1)
	{
		fscanf(f, "%s", cmd);

		if (strcmp(cmd, "push") == 0)
		{
			if (top == MAX_STACK_SIZE - 1)
			{
				printf("stack is full, cannot add element\n");
				printf("current stack elemenets : \n");
				sprint();
				exit(1);
			}

			top++;
			fscanf(f, "%d %s", &stack[top].id, stack[top].name);
		}
		else if (strcmp(cmd, "pop") == 0)
		{
			if (top == -1)
			{
				printf("Error: Stack is empty\n");
				exit(1);
			}
			else
			{
				top--;
			}
		}
		else if (strcmp(cmd, "sprint") == 0)
		{
			sprint();
		}
		else if (strcmp(cmd, "quit") == 0)
		{
			break;
		}
		else
		{
			printf("wrong command! try again!\n\n");

			int c;
			while ((c = fgetc(f)) != '\n' && c != EOF) {}
		}
	}
}