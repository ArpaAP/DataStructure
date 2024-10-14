#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;

listPointer first = NULL;

void printList(listPointer first)
{
	listPointer current = first;

	int i = 1;

	while (current != NULL)
	{
		printf("(%p, %4d, %p)", current, current->data, current->link);
		current = current->link;

		if (i % 3 == 0) printf("\n");
		i++;
	}
}

listPointer removeOdd(listPointer first)
{
	listPointer current = first;
	listPointer prev = NULL;

	while (current != NULL)
	{
		if (current->data % 2 == 1)
		{
			if (prev == NULL)
			{
				first = current->link;
			}
			else
			{
				prev->link = current->link;
			}

			listPointer temp = current;
			current = current->link;
			free(temp);
		}
		else
		{
			prev = current;
			current = current->link;
		}
	}

	return first;
}

void dropList(listPointer first)
{
	listPointer temp;

	while (first != NULL)
	{
		temp = first;
		first = first->link;
		free(temp);
	}
}

int main(void)
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL) {
		printf("File open error\n");
		return 1;
	}

	int n;

	while (!feof(f))
	{
		fscanf(f, "%d", &n);

		listPointer current = first;
		listPointer prev = NULL;

		while (current != NULL && current->data < n)
		{
			prev = current;
			current = current->link;
		}

		listPointer newNode = (listPointer)malloc(sizeof(listNode));
		newNode->data = n;
		newNode->link = current;

		if (prev == NULL)
		{
			first = newNode;
		}
		else
		{
			prev->link = newNode;
		}
	}

	fclose(f);

	printf("The ordered list contains:\n");
	printList(first);

	first = removeOdd(first);

	printf("\n\nAfter deleting nodes with odd value\n\n");
	printList(first);

	dropList(first);

	return 0;
}