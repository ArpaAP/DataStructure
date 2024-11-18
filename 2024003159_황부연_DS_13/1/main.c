#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_POINTER_LIST_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum { not, and, or, true, false } logical;
typedef struct treeNode* treePointer;
typedef struct treeNode {
	treePointer leftChild;
	logical data;
	short value;
	treePointer rightChild;
} treeNode;

treePointer stack[MAX_STACK_SIZE];
int top = -1;

treePointer createNode()
{
    treePointer p = (treePointer)malloc(sizeof(treeNode));

    p->data = false;
    p->value = 0;
    p->leftChild = NULL;
    p->rightChild = NULL;

    return p;
}

void push(treePointer p)
{
    stack[++top] = p;
}

treePointer pop()
{
    return stack[top--];
}


void printNode(treePointer p)
{
    printf("%d", p->data);
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

treePointer createBinaryTree(char* exp, short a, short b, short c)
{
    int len = strlen(exp);
    char ch;

    for (int i = 0; i < len; i++)
    {
        ch = exp[i];

        treePointer p = createNode();

        switch (ch)
        {
        case 'a':
            p->data = a ? true : false;
            p->value = a;
            break;
        case 'b':
            p->data = b ? true : false;
            p->value = b;
            break;
        case 'c':
            p->data = c ? true : false;
            p->value = c;
            break;
        case '~':
            p->data = not;
            p->rightChild = pop();
            break;
        case '&':
            p->data = and;
            p->rightChild = pop();
            p->leftChild = pop();
            break;
        case '|':
            p->data = or;
            p->rightChild = pop();
            p->leftChild = pop();
            break;
        }
            
        push(p);
    }

    return pop();
}

void postOrderEval(treePointer p)
{
    if (p)
    {
        postOrderEval(p->leftChild);
        postOrderEval(p->rightChild);
        switch (p->data)
        {
        case not:
            p->value = !p->rightChild->value;
            break;
        case and:
            p->value = p->rightChild->value && p->leftChild->value;
            break;
        case or:
            p->value = p->rightChild->value || p->leftChild->value;
            break;
        case true:
            p->value = 1;
            break;
        case false:
            p->value = 0;
            break;
        }
    }
}

int main(void)
{
    FILE* f;

    if ((f = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "file open error\n");
        return 1;
    }

    char exp[81];

    fgets(exp, 80, f);
    printf("input string (postfix) : %s\n", exp);

    printf("find true condition\n");

    treePointer root;

    for (int a = 0; a <= 1; a++)
    {
        for (int b = 0; b <= 1; b++)
        {
            for (int c = 0; c <= 1; c++)
            {
                root = createBinaryTree(exp, a, b, c);
                postOrderEval(root);

                if (root->value)
                {
                    printf("a=%d b=%d c=%d\n", a, b, c);
                }
            }
        }
    }

    fclose(f);

    return 0;
}
