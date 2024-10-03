#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 20
#define MALLOC(p, s) \
    if (!(p = malloc(s))) {\
        fprintf(stderr, "Insufficent memory"); \
        exit(EXIT_FAILURE); \
    }

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element *queue;
int capacity = 2;

int rear, front;

void copy(element* a, element* b, element* c)
{
	while (a != b)
	{
		*c++ = *a++;
	}
}

void queueFull()
{
	int start;
	element* newQueue;

	MALLOC(newQueue, 2 * capacity * sizeof(*newQueue));

	start = (front + 1) % capacity;
	if (start < 2)
	{
		copy(queue + start, queue + start + capacity - 1, newQueue);
	}
	else
	{
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	free(queue);
	queue = newQueue;
}

void qprint()
{
	int i = front;

	do
	{
		i = (i + 1) % capacity;
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

	MALLOC(queue, capacity * sizeof(*queue));

	while (1)
	{
		fscanf(f, "%s", cmd);

		if (strcmp(cmd, "add") == 0)
		{
			rear = (rear + 1) % capacity;

			if (front == rear)
			{
				queueFull();
				rear++;
				printf("queue capacity is doubled.\n");
				printf("current queue capacity is %d\n.", capacity);

				fscanf(f, "%d %s", &queue[rear].id, queue[rear].name);

				qprint();
			}
			else
			{
				fscanf(f, "%d %s", &queue[rear].id, queue[rear].name);
			}
		}
		else if (strcmp(cmd, "delete") == 0)
		{

			if (front == rear)
			{
				printf("queue is empty\n");
				exit(1);
			}

			front = (front + 1) % capacity;
		}
		else if (strcmp(cmd, "qprint") == 0)
		{
			qprint();
		}
		else if (strcmp(cmd, "quit") == 0)
		{
			printf("end of program!\n");
			fclose(f);
			return 0;
		}
		else
		{
			printf("wrong command! try again!\n\n");

			while ((c = fgetc(f)) != '\n' && c != EOF) {}
		}
	}
}