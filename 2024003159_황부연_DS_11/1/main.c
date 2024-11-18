#define _CRT_SECURE_NO_WARNINGS
#define MAX_QUEUE_SIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
	char data;
	treePointer leftChild, rightChild;
} treeNode;

treePointer createNode(char data)
{
	treePointer p = (treePointer)malloc(sizeof(treeNode));

	p->data = data;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}

void printNode(treePointer p)
{
	printf("(%p : %p %c %p)\n", p, p->leftChild, p->data, p->rightChild);
}

void inorder(treePointer p)
{
	if (p)
	{
		inorder(p->leftChild);
		printNode(p);
		inorder(p->rightChild);
	}
}

void preorder(treePointer p)
{
	if (p)
	{
		printNode(p);
		preorder(p->leftChild);
		preorder(p->rightChild);
	}
}

void postorder(treePointer p)
{
	if (p)
	{
		postorder(p->leftChild);
		postorder(p->rightChild);
		printNode(p);
	}
}

int main(void)
{
	printf("creating a binary tree\n");
	treePointer A = createNode('A');
	treePointer B = createNode('B');
	treePointer C = createNode('C');
	treePointer D = createNode('D');
	treePointer E = createNode('E');

	A->leftChild = B;
	A->rightChild = C;

	B->leftChild = D;
	B->rightChild = E;

	treePointer root = A;

	printf("\nthree binary tree traversals\n");
	printf("\ninorder traversal\n");
	inorder(root);

	printf("\npreorder traversal\n");
	preorder(root);

	printf("\npostorder traversal\n");
	postorder(root);

	return 0;
}