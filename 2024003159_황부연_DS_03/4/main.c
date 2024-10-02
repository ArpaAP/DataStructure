#include <stdio.h>
#define MAX_DEGREE 101
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
} polynomial;

void poly_print(char ch[], polynomial a)
{
	printf("%s(X) = ", ch);

	for (int i = 0; i < a.degree + 1; i++)
	{
		if (i < a.degree)
		{
			printf("%.2fx^%d + ", a.coef[i], a.degree - i);
		}
		else 
		{
			printf("%.2f", a.coef[i]);
		}
	}

	printf("\n");
}

int main(void)
{
	printf("<< C(x) = A(x) + B(x) >>\n");

	polynomial A, B, C;

	printf("Input the degree of items of A(x) : ");
	scanf_s("%d", &A.degree);
	printf("Input the coefficents A(x) : ");
	for (int i = 0; i < A.degree + 1; i++)
	{
		scanf_s("%f", &A.coef[i]);
	}

	printf("Input the degree of items of B(x) : ");
	scanf_s("%d", &B.degree);
	printf("Input the coefficents B(x) : ");
	for (int i = 0; i < B.degree + 1; i++)
	{
		scanf_s("%f", &B.coef[i]);
	}

	poly_print("A", A);
	poly_print("B", B);

	int Apos = 0, Bpos = 0, Cpos = 0;
	int Adeg = A.degree;
	int Bdeg = B.degree;

	C.degree = MAX(A.degree, B.degree);

	while (Apos <= A.degree && Bpos <= B.degree) {
		if (Adeg > Bdeg) {
			C.coef[Cpos++] = A.coef[Apos++];
			Adeg--;
		}
		else if (Adeg < Bdeg) {
			C.coef[Cpos++] = B.coef[Bpos++];
			Bdeg--;
		}
		else { 
			C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
			Adeg--;
			Bdeg--;
		}
	}

	poly_print("C", C);

	return 0;
}