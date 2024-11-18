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
    return stack[top--];
}


void printNode(treePointer p)
{
    printf("%c", p->data);
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

    printf("\ninorder traversal   : ");
    inorder(root);

    printf("\npreorder traversal  : ");
    preorder(root);

    printf("\npostorder traversal : ");
    postorder(root);

    return 0;
}
