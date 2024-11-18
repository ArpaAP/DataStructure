#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	int n;
	nodePointer link;
} node;

nodePointer createNode(int n)
{
	nodePointer tmp = (nodePointer)malloc(sizeof(node));
	tmp->n = n;
	tmp->link = NULL;

	return tmp;
}

void insertFirst(nodePointer *head, int n)
{
	nodePointer tmp = createNode(n);

	if (*head) tmp->link = *head;
	*head = tmp;
}

void printList(nodePointer head)
{
	nodePointer p = head;

	while (p != NULL)
	{
		printf("%4d", p->n);
		p = p->link;
	}
	printf("\n");
}

int main(void)
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "file open error\n");
		exit(EXIT_FAILURE);
	}

	char type;
	int vertices, edges;
	fscanf(f, "%c %d %d", &type, &vertices, &edges);

	nodePointer* adjList = (nodePointer*)malloc(sizeof(nodePointer) * vertices);
	if (adjList == NULL)
	{
		fprintf(stderr, "insufficient memory\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < vertices; i++)
	{
		adjList[i] = NULL;
	}

	int a, b;
	for (int i = 0; i < edges; i++)
	{
		fscanf(f, "%d %d", &a, &b);
		insertFirst(&adjList[a], b);
		if (type == 'u')
		{
			insertFirst(&adjList[b], a);
		}
	}

	fclose(f);

	for (int i = 0; i < vertices; i++)
	{
		printf("adjList[%d] : ", i);
		printList(adjList[i]);
	}

	return 0;
}