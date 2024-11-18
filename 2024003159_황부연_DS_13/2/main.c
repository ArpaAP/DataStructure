#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct threadedNode* threadedPointer;
typedef struct threadedNode {
	short leftThread, rightThread;
	threadedPointer leftChild, rightChild;
	char data;
} threadedNode;

threadedPointer createNode(char data)
{
	threadedPointer p = (threadedPointer)malloc(sizeof(threadedNode));
	p->data = data;
	p->leftThread = 0;
	p->rightThread = 0;
	p->leftChild = NULL;
	p->rightChild = NULL;

	return p;
}

threadedPointer insucc(threadedPointer root)
{
	threadedPointer p;
	p = root->rightChild;
	if (!root->rightThread)
	{
		while (!p->leftThread)
		{
			p = p->leftChild;
		}
	}

	return p;
}

void tinorder(threadedPointer root)
{
	threadedPointer p = root;

	while (1)
	{
		p = insucc(p);
		if (p == root) break;
		printf("%p(%d, %p, %c, %d, %p)\n", p, p->leftThread, p->leftChild, p->data, p->rightThread, p->rightChild);
	}
}



int main(void)
{
	threadedPointer root = createNode(' ');
	threadedPointer A = createNode('A');
	threadedPointer B = createNode('B');
	threadedPointer C = createNode('C');
	threadedPointer D = createNode('D');
	threadedPointer E = createNode('E');
	threadedPointer F = createNode('F');
	threadedPointer G = createNode('G');
	threadedPointer H = createNode('H');
	threadedPointer I = createNode('I');

	root->leftChild = A;
	root->rightChild = root;

	A->leftChild = B;
	A->rightChild = C;

	B->leftChild = D;
	B->rightChild = E;

	E->leftChild = B;
	E->rightChild = A;
	E->leftThread = 1;
	E->rightThread = 1;

	C->leftChild = F;
	C->rightChild = G;

	F->leftChild = A;
	F->rightChild = C;
	F->leftThread = 1;
	F->rightThread = 1;

	G->leftChild = C;
	G->rightChild = root;
	G->leftThread = 1;
	G->rightThread = 1;

	D->leftChild = H;
	D->rightChild = I;

	H->leftChild = root;
	H->rightChild = D;
	H->leftThread = 1;
	H->rightThread = 1;

	I->leftChild = D;
	I->rightChild = B;
	I->leftThread = 1;
	I->rightThread = 1;

	printf("%p(%d, %p, %c, %d, %p)\n", root, root->leftThread, root->leftChild, root->data, root->rightThread, root->rightChild);
	tinorder(root);
}