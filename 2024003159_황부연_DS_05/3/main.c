#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];

int rear, front;

void qprint()
{
	int i = front;

	do
	{
		i = (i + 1) % MAX_QUEUE_SIZE;
		printf("%d %s\n", queue[i].id, queue[i].name);
	} while (i != rear);
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
			if ((rear + 1) % MAX_QUEUE_SIZE == front)
			{
				printf("queue is full, not added\n");
				while ((c = fgetc(f)) != '\n' && c != EOF) {}
				continue;
			}

			rear = (rear + 1) % MAX_QUEUE_SIZE;
			fscanf(f, "%d %s", &queue[rear].id, queue[rear].name);
		}
		else if (strcmp(cmd, "delete") == 0)
		{
			
			if (front == rear)
			{
				printf("queue is empty\n");
				exit(1);
			}

			front = (front + 1) % MAX_QUEUE_SIZE;
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