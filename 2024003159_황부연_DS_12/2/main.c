#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100
#define MAX_QUEUE_SIZE 100
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

treePointer tmpStack[MAX_STACK_SIZE];
int tmpTop = -1;

treePointer queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

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

void enqueue(treePointer p)
{
    queue[rear++] = p;
}

treePointer dequeue()
{
    if (front == rear) return NULL;
    return queue[front++];
}


void printNode(treePointer p)
{
    printf("%c", p->data);
}

void iterInorder(treePointer p)
{
    while (1)
    {
        while (p)
        {
            push(p);
            tmpStack[++tmpTop] = p;
            p = p->leftChild;
        }

        p = pop();

        if (!p) break;
        printf("%c ", p->data);
        p = p->rightChild;
    }
}

void levelOrder(treePointer p)
{
    if (!p) return;
    enqueue(p);

    while (1)
    {
        p = dequeue();

        if (!p) break;

        printf("%c ", p->data);
        if (p->leftChild)
        {
            enqueue(p->leftChild);
        }
        if (p->rightChild)
        {
            enqueue(p->rightChild);
        }
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

    printf("\niterative inorder traversal   : ");
    iterInorder(root);

    printf("\n스택에 들어가는 데이터의 순서 : ");
    for (int i = 0; i <= tmpTop; i++)
    {
        printf("%c ", tmpStack[i]->data);
    }

    printf("\nlevel order traversal         : ");
    levelOrder(root);

    return 0;
}
