#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

#include <stdio.h>

static int isp[] = { 0, 19, 12, 12, 13, 13, 13 ,0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

precedence stack[MAX_STACK_SIZE];

char expr[MAX_EXPR_SIZE];

int top = -1;

void push(precedence token)
{
	stack[++top] = token;
}

precedence pop()
{
	return stack[top--];
}

precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

int eval(void)
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;

	while ((token = getToken(&symbol, &n)) != eos)
	{
		if (token == operand)
			push(symbol - '0');
		else
		{
			op2 = pop();
			op1 = pop();
			switch (token)
			{
			case plus: push(op1 + op2); break;
			case minus: push(op1 - op2); break;
			case times: push(op1 * op2); break;
			case divide: push(op1 / op2); break;
			case mod: push(op1 % op2); break;
			}
		}
	}
	return pop();
}

int main(void)
{
	FILE *inputFile, *outputFile;

	if ((inputFile = fopen("input.txt", "r")) == NULL)
	{
		printf("File open error\n");
		return 0;
	}

	if ((outputFile = fopen("output.txt", "w")) == NULL)
	{
		printf("File open error\n");
		return 0;
	}

	int i = 0;

	while (!feof(inputFile))
	{
		fscanf(inputFile, "%c ", &expr[i++]);
	}

	expr[i] = '\0';

	fclose(inputFile);

	printf("postfix expression : ");
	fprintf(outputFile, "postfix expression : ");

	for (int j = 0; j < i; j++)
	{
		printf("%c ", expr[j]);
		fprintf(outputFile, "%c ", expr[j]);
	}

	int result = eval();

	printf("\nthe evaluation value : %d\n", result);
	fprintf(outputFile, "\nthe evaluation value : %d\n", result);

	fclose(outputFile);

	return 0;
}
