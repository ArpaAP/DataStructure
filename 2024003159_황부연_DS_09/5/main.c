#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)


typedef struct polyNode* polyPointer;
typedef struct polyNode {
	int coef;
	int exp;
	polyPointer link;
} polyNode;

polyPointer avail = NULL;

polyPointer getNode()
{
	polyPointer p;

	if (avail)
	{
		p = avail;
		avail = avail->link;
	}
	else
	{
		p = (polyPointer)malloc(sizeof(polyNode));
	}

	return p;
}

void retNode(polyPointer p)
{
	p->link = avail;
	avail = p;
}

polyPointer insertFront(polyPointer head, polyPointer p)
{
	if (head == NULL)
	{
		p->link = p;
		head = p;
	}
	else
	{
		p->link = head->link;
		head->link = p;
	}

	return head;
}

polyPointer insertLast(polyPointer head, polyPointer p)
{
	if (head == NULL)
	{
		p->link = p;
		head = p;
	}
	else
	{
		p->link = head->link;
		head->link = p;
		head = p;
	}

	return head;
}

void attach(int coff, int exp, polyPointer* ptr) {
	polyPointer temp = getNode();

	temp->coef = coff;
	temp->exp = exp;
	*ptr = insertLast(*ptr, temp);
}

polyPointer createPoly(FILE* fp)
{
	char sort;
	int coef, exp;
	fscanf(fp, "%c", &sort);

	polyPointer head = NULL;

	if (sort == 'd')
	{
		head = getNode();
		head->coef = -1;
		head->exp = -1;
		head->link = head;		

		while (fscanf(fp, "%d %d", &coef, &exp) != EOF)
		{
			polyPointer p = getNode();
			p->coef = coef;
			p->exp = exp;

			head = insertLast(head, p);
		}
	}
	else
	{
		while (fscanf(fp, "%d %d", &coef, &exp) != EOF)
		{
			polyPointer p = getNode();
			p->coef = coef;
			p->exp = exp;

			head = insertFront(head, p);
		}

		polyPointer tmp = getNode();
		tmp->coef = -1;
		tmp->exp = -1;
		insertFront(head, tmp);
	}

	return head->link;
}

void printList(polyPointer head)
{
	polyPointer p = head;

	do {
		printf("(%p : %5dx^%d : %p)\n", p, p->coef, p->exp, p->link);
		p = p->link;
	} while (p != head);
}

void printAvail()
{
	polyPointer p = avail;

	while (p)
	{
		printf("(%p : %5dx^%d : %p)\n", p, p->coef, p->exp, p->link);
		p = p->link;
	}
}

polyPointer cpadd(polyPointer A, polyPointer B) { // ´ÙÇ×½Ä µ¡¼À ÇÔ¼ö
	polyPointer startA, C, lastC;
	int sum, done = 0;

	startA = A;
	A = A->link;
	B = B->link;
	C = getNode();

	C->coef = -1;
	C->exp = -1;
	C->link = C;
	lastC = C;

	do {
		switch (COMPARE(A->exp, B->exp)) {
		case -1:
			attach(B->coef, B->exp, &lastC);
			B = B->link;
			break;
		case 0:
			if (startA == A) done = 1;
			else {
				sum = A->coef + B->coef;
				if (sum) attach(sum, A->exp, &lastC);
				A = A->link; B = B->link;
			}
			break;
		case 1:
			attach(A->coef, A->exp, &lastC);
			A = A->link;
		}
	} while (!done);

	return C;
}

void cerase(polyPointer* head)
{
	polyPointer tmp;

	if (*head)
	{
		tmp = (*head)->link;
		(*head)->link = avail;
		avail = tmp;
		*head = NULL;
	}
}

int main(void)
{
	FILE* fa, * fb;

	if ((fa = fopen("a.txt", "r")) == NULL)
	{
		fprintf(stderr, "a.txt open error\n");
		return 1;
	}

	if ((fb = fopen("b.txt", "r")) == NULL)
	{
		fprintf(stderr, "b.txt open error\n");
		return 1;
	}

	polyPointer headA = createPoly(fa);
	polyPointer headB = createPoly(fb);
	polyPointer headC = cpadd(headA, headB);

	printf("\na:\n");
	printList(headA);

	printf("\nb:\n");
	printList(headB);

	printf("\na + b = c:\n");
	printList(headC);

	cerase(&headA);
	cerase(&headB);
	cerase(&headC);

	printf("\navail:\n");
	printAvail();

	fclose(fa);
	fclose(fb);

	return 0;
}