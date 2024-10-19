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

polyPointer a = NULL;
polyPointer b = NULL;

polyPointer insertFront(polyPointer head, int coef, int exp)
{
	polyPointer temp = (polyPointer)malloc(sizeof(polyNode));
	temp->coef = coef;
	temp->exp = exp;
	temp->link = head;

	return temp;
}

polyPointer insertLast(polyPointer head, int coef, int exp)
{
	polyPointer temp = (polyPointer)malloc(sizeof(polyNode));
	temp->coef = coef;
	temp->exp = exp;
	temp->link = NULL;

	if (head == NULL)
	{
		return temp;
	}

	polyPointer p = head;

	while (p->link != NULL)
	{
		p = p->link;
	}

	p->link = temp;

	return head;
}

void attach(int coef, int exp, polyPointer* ptr)
{
	polyPointer temp = (polyPointer)malloc(sizeof(polyNode));
	temp->coef = coef;
	temp->exp = exp;
	(*ptr)->link = temp;
	*ptr = temp;
}

polyPointer inputData(polyPointer head, FILE *fp)
{
	char sort;
	fscanf(fp, "%c", &sort);

	int coef, exp;

	while (fscanf(fp, "%d %d", &coef, &exp) != EOF)
	{
		head = sort == 'a' ? insertFront(head, coef, exp) : insertLast(head, coef, exp);
	}

	return head;
}

void printList(polyPointer head)
{
	polyPointer p = head;

	while (p != NULL)
	{
		printf("(%p : %+5dx^%d : %p)\n", p, p->coef, p->exp, p->link);
		p = p->link;
	}
	printf("\n");
}

polyPointer padd(polyPointer a, polyPointer b)
{
	polyPointer c, temp;
	int sum;

	polyPointer rear = (polyPointer)malloc(sizeof(polyNode));

	c = rear;

	while (a && b)
	{
		switch (COMPARE(a->exp, b->exp))
		{
		case -1:
			attach(b->coef, b->exp, &rear);
			b = b->link;
			break;
		case 0:
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->exp, &rear);
			a = a->link;
			b = b->link;
			break;
		case 1:
			attach(a->coef, a->exp, &rear);
			a = a->link;
			break;
		}
	}

	for (; a; a = a->link)
		attach(a->coef, a->exp, &rear);

	for (; b; b = b->link)
		attach(b->coef, b->exp, &rear);

	rear->link = NULL;

	temp = c;
	c = c->link;
	free(temp);
	
	return c;
}

void drop(polyPointer head)
{
	polyPointer p;

	while (head)
	{
		p = head;
		head = head->link;
		free(p);
	}
}

int main(void)
{
	FILE *fa, *fb;

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

	a = inputData(a, fa);
	b = inputData(b, fb);

	printf("\na:\n");
	printList(a);

	printf("\nb:\n");
	printList(b);
	
	polyPointer headC = padd(a, b);

	printf("\na + b = c:\n");
	printList(headC);

	drop(a);
	drop(b);

	fclose(fa);
	fclose(fb);

	return 0;
}