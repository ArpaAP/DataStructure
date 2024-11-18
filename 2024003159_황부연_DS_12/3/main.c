#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
    char data;
    treePointer leftChild, rightChild;
} treeNode;

treePointer stack[MAX_STACK_SIZE];
int top = -1;

treePointer createNode(char data)
{
    treePointer p = (treePointer)malloc(sizeof(treeNode));

    p->data = data;
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
    if (top == -1)
    {
        return NULL;
    }
    return stack[top--];
}

void printNode(treePointer p)
{
    printf("%c", p->data);
}

void iterPostorder(treePointer p)
{
    treePointer lastVisited = NULL;
    treePointer current = p;

    while (top != -1 || current != NULL)
    {
        if (current != NULL)
        {
            push(current);
            current = current->leftChild;
        }
        else
        {
            treePointer peekNode = stack[top];
            if (peekNode->rightChild != NULL && lastVisited != peekNode->rightChild)
            {
                current = peekNode->rightChild;
            }
            else
            {
                printNode(peekNode);
                lastVisited = pop();
                current = NULL;
            }
        }
    }
}

void iterPreorder(treePointer p)
{
    if (p == NULL)
        return;

    push(p);

    while (top != -1)
    {
        treePointer node = pop();
        printNode(node);

        if (node->rightChild != NULL)
            push(node->rightChild);

        if (node->leftChild != NULL)
            push(node->leftChild);
    }
}



treePointer createBinaryTree(char* exp)
{
    int len = strlen(exp);
    char c;

    for (int i = 0; i < len; i++)
    {
        c = exp[i];

        treePointer p = createNode(c);

        if (!isalpha(c)) {
            p->rightChild = pop();
            p->leftChild = pop();
        }
        push(p);
    }

    return pop();
}

int main(void)
{
    FILE* f;

    if ((f = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "file open error\n");
        return 1;
    }

    printf("the length of input string should be less than 80\n");
    char exp[81];

    fgets(exp, 80, f);
    printf("input string (postfix expression) : %s\n", exp);

    printf("creating its binary tree\n");

    treePointer root = createBinaryTree(exp);

    fclose(f);

    printf("\niterative postorder traversal   : ");
    iterPreorder(root);
    printf("\niterative postorder traversal   : ");
    iterPostorder(root);

    return 0;
}
