#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_TERMS 100
#define COMPARE(x,y) (((x) < (y)) ? -1: ((x) == (y)) ? 0 : 1)

typedef struct {
	float coef;
	int expon;
} term;

term terms[MAX_TERMS];

int avail;

void attach(float coefficient, int exponent)
{
	if (avail >= MAX_TERMS)
	{
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail].expon = exponent;
	avail++;
}

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD)
{
	float coefficient;
	*startD = avail;

	while (startA <= finishA && startB <= finishB)
	{
		switch (COMPARE(terms[startA].expon, terms[startB].expon))
		{
			case -1:
				attach(terms[startB].coef, terms[startB].expon);
				startB++;
				break;
			case 0:
				coefficient = terms[startA].coef + terms[startB].coef;

				if (coefficient)
				{
					attach(coefficient, terms[startA].expon);
				}
				startA++;
				startB++;
				break;
			case 1:
				attach(terms[startA].coef, terms[startA].expon);
				startA++;
				break;
		}
	}

	for (; startA <= finishA; startA++)
		attach(terms[startA].coef, terms[startA].expon);

	for (; startB <= finishB; startB++)
	{
		attach(terms[startB].coef, terms[startB].expon);
	}

	*finishD = avail - 1;

}

void print_poly(char c[], int start, int finish)
{
	int i;

	printf("%s(x) = ", c);

	for (i = start; i < finish - 1; i++)
	{
		printf("%.2fx^%d + ", terms[i].coef, terms[i].expon);
	}

	printf("%.2fx^%d\n", terms[i].coef, terms[i].expon);
}

int main(void)
{
	int numA, numB;

	printf("<< D(x) = A(x) + B(x) >>\n");

	printf("Input the number of items of A(x) : ");
	scanf_s("%d", &numA);
	printf("Input the number of items of B(x) : ");
	scanf_s("%d", &numB);

	printf("\nInput in descending order\n");
	printf("coefficient and exponent of A(x)=10x^5+8x^3+7 (10 5, 8 3, 7 0) : ");

	int startA = 0;
	int finishA = numA;
	int startB = numA + 1;
	int finishB = startB + numB;
	avail = finishB + 1;

	for (int i = startA; i < finishA; i++)
	{
		scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
	}

	printf("coefficient and exponent of B(x)=10x^5+8x^2+3 (10 5, 8 2, 3 0) : ");
	for (int i = startB; i < finishB; i++)
	{
		scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
	}

	int startD, finishD;

	print_poly("A", startA, finishA);
	print_poly("B", startB, finishB);

	padd(startA, finishA, startB, finishB, &startD, &finishD);

	print_poly("D", startD, finishD);

	return 0;
}