#define _CRT_SECURE_NO_WARNINGS
#define MEMORY_SIZE 10
#define MAX_STACKS 4
#define MAX_NAME_SIZE 10

#include <stdio.h>
#include <string.h>

typedef struct {
	char name[MAX_NAME_SIZE];
} element;

element memory[MEMORY_SIZE];

FILE* f;

int top[MAX_STACKS];
int boundary[MAX_STACKS];
int n;

void push(int i, element item)
{
	if (top[i] == boundary[i + 1])
	{
		printf("Stack %d is full\n", i);
		return;
	}

	memory[++top[i]] = item;
	printf("%s is pushed in Stack No. %d\n", item.name, i);
}

element pop(int i)
{
	if (top[i] == boundary[i])
	{
		printf("Stack %d is empty\n", i);
		return;
	}

	printf("%s is popped from Stack No. %d\n", memory[top[i]].name, i);
	return memory[top[i]--];
}

void sprint(int i)
{
	printf("\n");

	if (top[i] == boundary[i])
	{
		printf("Stack %d is empty\n", i);
		return;
	}

	for (int j = top[i]; j > boundary[i]; j--)
	{
		printf("%s\n", memory[j].name);
	}

	printf("\n");
}

void sprintAll()
{
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("Stack %d:", i);
		sprint(i);
		printf("\n");
	}
}

int main(void)
{
	if ((f = fopen("input.txt", "r")) == NULL)
	{
		printf("File open error\n");
		return 1;
	}

	printf("How many stacks? : ");
	scanf("%d", &n);
	printf("\n");

	if (n >= MAX_STACKS)
	{
		printf("Too many stacks\n");
		return 1;
	}

	for (int i = 0; i < n; i++)
	{
		top[i] = boundary[i] = i * (MEMORY_SIZE / n) - 1;
	}

	boundary[n] = MEMORY_SIZE - 1;

	int i;
	char cmd[100];

	while (!feof(f))
	{
		fscanf(f, "%s", cmd);

		if (strcmp(cmd, "add") == 0)
		{
			element item;

			fscanf(f, "%d %s", &i, item.name);

			if (i >= n)
			{
				printf("stack number error, try again\n");
				continue;
			}

			push(i, item);
		}
		else if (strcmp(cmd, "delete") == 0)
		{
			fscanf(f, "%d", &i);

			if (i >= n)
			{
				printf("stack number error, try again\n");
				continue;
			}

			element item = pop(i);
		}
		else if (strcmp(cmd, "sprint") == 0)
		{
			fscanf(f, "%d", &i);

			if (i >= n)
			{
				printf("stack number error, try again\n");
				continue;
			}

			sprint(i);
		}
		else if (strcmp(cmd, "quit") == 0)
		{
			printf("\nProgram end\n");
			sprintAll();

			break;
		}
		else
		{
			printf("wrong command, try again!!\n");

			while (fgetc(f) != '\n');
		}
	}

	fclose(f);

	return 0;
}