#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
} node;

nodePointer head = NULL;

void dinsert(nodePointer node, nodePointer newNode)
{
	newNode->llink = node;
	newNode->rlink = node->rlink;
	node->rlink->llink = newNode;
	node->rlink = newNode;
}

void print_forward(nodePointer head)
{
	nodePointer temp = head->rlink;
	int i = 0;

	printf("forward\n");
	while (temp != head)
	{
		printf("(%p %5d %p)    ", temp, temp->data, temp->rlink);

		if (i % 4 == 3)
			printf("\n");
		temp = temp->rlink;
		i++;
	}
	printf("\n");
}

void print_backward(nodePointer head)
{
	nodePointer temp = head->llink;
	int i = 0;

	printf("\nbackward\n");
	while (temp != head)
	{
		printf("(%p %5d %p)    ", temp, temp->data, temp->rlink);

		if (i % 4 == 3)
			printf("\n");
		temp = temp->llink;
		i++;
	}
	printf("\n");
}

int main(void)
{
	FILE* f;

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "Cannot open the file\n");
		exit(1);
	}

	int n;

	while (fscanf(f, "%d", &n) != EOF)
	{
		nodePointer newNode = (nodePointer)malloc(sizeof(node));
		newNode->data = n;

		if (head == NULL)
		{
			head = (nodePointer)malloc(sizeof(node));
			head->llink = head;
			head->rlink = head;
		}

		dinsert(head->llink, newNode);
	}

	print_forward(head);
	print_backward(head);

	nodePointer temp = head->rlink;
	nodePointer next;

	while (temp != head)
	{
		next = temp->rlink;

		if (temp->data <= 50)
		{
			temp->llink->rlink = temp->rlink;
			temp->rlink->llink = temp->llink;
			free(temp);
		}

		temp = next;
	}

	printf("After deleting numbers less than and equal to 50 :\n");

	print_forward(head);
	print_backward(head);

	return 0;
}