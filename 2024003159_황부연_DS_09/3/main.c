#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

listPointer first = NULL;

void insertLast(listPointer node)
{
	if (first == NULL)
	{
		first = node;
		node->link = first;
	}
	else
	{	
		node->link = first->link;
		first->link = node;
		first = node;
	}
}

void delete(listPointer target)
{
	if (target == target->link)
	{
		free(target);
		first = NULL;
		return;
	}

	listPointer prev = target;

	while (prev->link != target)
	{
		prev = prev->link;
	}

	prev->link = target->link;

	if (first == target) first = prev;

	free(target);
}

void print()
{
	if (first == NULL) return;

	int i = 0;

	listPointer current = first->link;

	printf("The Circularly Linked List contains:\n");

	do {
		printf("(%p, %5d, %p)", current, current->data, current->link);
		
		if (i % 3 == 2) {
			printf("\n");
		}

		i++;
		current = current->link;
	} while (current != first->link);
}

void drop()
{
	listPointer current = first->link;
	listPointer tmp;

	while (first != NULL)
	{
		tmp = current->link;
		delete(current);
		current = tmp;
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

	while (!feof(f))
	{
		listPointer node = (listPointer)malloc(sizeof(listNode));

		if (node == NULL)
		{
			printf("Insufficient memory");
			return 1;
		}

		fscanf(f, "%d", &node->data);

		insertLast(node);
	}

	print(first);

	listPointer current = first->link;
	listPointer tmp;

	do {
		if (current->data % 2 == 1)
		{
			tmp = current->link;
			delete(current);
			current = tmp;
		}
		else
		{
			current = current->link;
		}
		
	} while (current != first->link);

	printf("\n\nAfter deleting nodes with odd value\n\n");

	print(first);

	drop();

	return 0;
}