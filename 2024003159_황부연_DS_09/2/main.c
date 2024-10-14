#define _CRT_SECURE_NO_WARNINGS
#define MAX_QUEUES 3
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int class_num;
	int score;
} element;

typedef struct queueNode* queuePointer;
typedef struct queueNode {
	element data;
	queuePointer next;
} queueNode;

queuePointer front[MAX_QUEUES], rear[MAX_QUEUES];

void add(int i, element item)
{
	queuePointer temp = (queuePointer)malloc(sizeof(queueNode));

	temp->data = item;
	temp->next = NULL;

	if (front[i])
		rear[i]->next = temp;
	else 
		front[i] = temp;
	rear[i] = temp;
}

void print()
{
	queuePointer current;

	printf("과목번호, 학반, 성적\n");
	for (int i = 0; i < MAX_QUEUES; i++)
	{
		printf("********************\n");

		current = front[i];
		while (current != NULL)
		{
			element item = current->data;
			printf("%8d %5d %4d\n", i, item.class_num, item.score);
			current = current->next;
		}
	}
}
int main(void)
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		printf("file open error\n");
		return 1;
	}

	for (int i = 0; i < MAX_QUEUES; i++)
	{
		front[i] = NULL;
		rear[i] = NULL;
	}

	int subject_num, class_num, score;
	while (!feof(f))
	{
		fscanf(f, "%d %d %d", &subject_num, &class_num, &score);

		element item;
		item.class_num = class_num;
		item.score = score;

		add(subject_num, item);
	}

	fclose(f);

	print();

	return 0;
}