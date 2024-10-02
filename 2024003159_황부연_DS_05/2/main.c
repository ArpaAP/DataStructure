#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 100

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

void qprint()
{
	for (int i = front + 1; i <= rear; i++)
	{
		printf("%d %s\n", queue[i].id, queue[i].name);
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

	int c;
	char cmd[100];

	while (1)
	{
		fscanf(f, "%s", cmd);

		if (strcmp(cmd, "add") == 0)
		{
			if (rear == MAX_QUEUE_SIZE - 1)
			{
				if (rear - front == MAX_QUEUE_SIZE)
				{
					printf("queue is full, not added\n");
					while ((c = fgetc(f)) != '\n' && c != EOF) {}
					continue;
				}
				else {
					printf("data shift\n");

					for (int i = front + 1; i <= rear; i++)
					{
						queue[i - front - 1] = queue[i];
					}

					rear = rear - front - 1;
					front = -1;
				}
			}

			rear++;
			fscanf(f, "%d %s", &queue[rear].id, queue[rear].name);
		}
		else if (strcmp(cmd, "delete") == 0)
		{
			if (front == rear)
			{
				printf("queue is empty, cannot delete element.\n");
				exit(1);
			}

			front++;
		}
		else if (strcmp(cmd, "qprint") == 0)
		{
			qprint();
		}
		else if (strcmp(cmd, "quit") == 0)
		{
			break;
		}
		else
		{
			printf("wrong command! try again!\n\n");

			while ((c = fgetc(f)) != '\n' && c != EOF) {}
		}
	}
}