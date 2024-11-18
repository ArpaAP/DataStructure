#define _CRT_SECURE_NO_WARNINGS
#define MAX_QUEUE_SIZE 100
#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode* treePointer;
typedef struct treeNode {
    char data;
    treePointer leftChild, rightChild;
} treeNode;

treePointer createNode(char data)
{
    treePointer p = (treePointer)malloc(sizeof(treeNode));

    p->data = data;
    p->leftChild = NULL;
    p->rightChild = NULL;

    return p;
}

treePointer queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

void enqueue(treePointer p)
{
    queue[rear++] = p;
}

treePointer dequeue(void)
{
    return queue[front++];
}

void printNode(treePointer p)
{
    printf("%c ", p->data);
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

treePointer insert(treePointer root, char data)
{
    treePointer tmp = createNode(data);
    enqueue(tmp);

    if (root == NULL)
    {
        root = tmp;   
    }
    else
    {
        treePointer current = queue[front];

        if (current->leftChild == NULL)
        {
            current->leftChild = tmp;
        }
        else if (current->rightChild == NULL)
        {
            current->rightChild = tmp;
            dequeue();
        }
    }

    return root;
}

int main(void)
{
    FILE* f;
    treePointer root = NULL;

    if ((f = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "file open error\n");
        return 1;
    }

    char c;
    while (fscanf(f, "%c", &c) == 1)
    {
        root = insert(root, c);
    }

    fclose(f);

    printf("creating a complete binary tree\n");

    printf("\nthree binary tree traversals\n");

    printf("inorder traversal : ");
    inorder(root);
    printf("\n");

    printf("preorder traversal : ");
    preorder(root);
    printf("\n");

    printf("postorder traversal : ");
    postorder(root);
    printf("\n");

    return 0;
}
