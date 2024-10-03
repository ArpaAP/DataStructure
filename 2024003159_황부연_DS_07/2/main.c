#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

#include <stdio.h>
#include <string.h>

static int isp[] = { 0, 19, 12, 12, 13, 13, 13 ,0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

precedence stack[MAX_STACK_SIZE];

char infixExpr[MAX_EXPR_SIZE];
char postExpr[MAX_EXPR_SIZE];

int top = -1;

void push(precedence token)
{
	stack[++top] = token;
}

precedence pop()
{
	return stack[top--];
}

precedence getToken(char* symbol, int* n, char* expr)
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

char getSymbol(precedence token)
{
	switch (token)
	{
	case lparen: return '(';
	case rparen: return ')';
	case plus: return '+';
	case minus: return '-';
	case times: return '*';
	case divide: return '/';
	case mod: return '%';
	default: return '\0';
	}
}

void postfix(void)
{
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;

	int i = 0;

	while ((token = getToken(&symbol, &n, infixExpr)) != eos)
	{
		if (token == operand)
		{
			postExpr[i++] = symbol;
		}
		else if (token == rparen)
		{
			while (stack[top] != lparen)
			{
				postExpr[i++] = getSymbol(pop());
			}
			pop();
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
			{
				postExpr[i++] = getSymbol(pop());
			}
			push(token);
		}
	}

	while ((token = pop()) != eos)
	{
		postExpr[i++] = getSymbol(token);
	}
	postExpr[i] = '\0';
}

int main(void)
{
	FILE* inputFile, * outputFile;

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

	fgets(infixExpr, MAX_EXPR_SIZE, inputFile);

	fclose(inputFile);

	printf("<< Infix to Postfix >>\n");
	printf("Infix expression : %s\n", infixExpr);

	postfix();

	int size = strlen(postExpr);

	printf("postfix expression : ");

	for (int j = 0; j < size; j++)
	{
		printf("%c ", postExpr[j]);
		fprintf(outputFile, "%c ", postExpr[j]);
	}

	fclose(outputFile);

	return 0;
}
