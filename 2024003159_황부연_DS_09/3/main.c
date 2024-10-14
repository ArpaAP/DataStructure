#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

listPointer first = NULL;

void insertFront(listPointer* last, listPointer node)
{
	if (!(*last))
	{
		*last = node;
		node->link = node;
	}
	else {
		node->link = (*last)->link;
		(*last)->link = node;
	}
}

void print()
{

}

int main(void)
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		printf("file open error\n");
		return 1;
	}

	listPointer last = first;

	while (!feof(f))
	{
		listPointer node = (listPointer)malloc(sizeof(listNode));

		if (node == NULL)
		{
			printf("Insufficient memory");
			return 1;
		}

		fscanf(f, "%d", &node->data);

		insertFront(&last, node);
	}

	return 0;
}