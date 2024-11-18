#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 500
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int item;
} element;

typedef struct treeNode* treePointer;
typedef struct treeNode {
    element data;
    treePointer leftChild, rightChild;
} treeNode;

element elements[MAX_SIZE];

element* search(treePointer root, int k)
{
    if (!root) return NULL;
    if (k == root->data.key) return &(root->data);
    if (k < root->data.key)
    {
        return search(root->leftChild, k);
    }
    return search(root->rightChild, k);
}

element* searchWithPrint(treePointer root, int k)
{
    if (!root) return NULL;
    printf("%d => ", root->data.key);
    if (k == root->data.key) return &(root->data);
    if (k < root->data.key)
    {
        return searchWithPrint(root->leftChild, k);
    }
    return searchWithPrint(root->rightChild, k);
}

void insert(treePointer* node, int k, int theItem)
{
    treePointer ptr, temp, parent;

    temp = *node;
    parent = NULL;

    while (temp != NULL)
    {
        parent = temp;
        if (k == temp->data.key)
        {
            return;
        }
        else if (k < temp->data.key)
        {
            temp = temp->leftChild;
        }
        else
        {
            temp = temp->rightChild;
        }
    }

    ptr = (treePointer)malloc(sizeof(treeNode));
    ptr->data.key = k;
    ptr->data.item = theItem;
    ptr->leftChild = ptr->rightChild = NULL;

    if (parent != NULL)
    {
        if (k < parent->data.key)
            parent->leftChild = ptr;
        else
            parent->rightChild = ptr;
    }
    else
    {
        *node = ptr;
    }
}

void inorderTraversal(treePointer root)
{
    if (root)
    {
        inorderTraversal(root->leftChild);
        printf("%4d", root->data.key);
        inorderTraversal(root->rightChild);
    }
}


int main(void)
{
    printf("random number generation (1 ~ %d)\n", MAX_SIZE);
    printf("the number of nodes in BST (less than and equal to 50) : ");

    int n;
    unsigned int seed;
    scanf("%d", &n);

    if (n <= 0 || n > 50)
    {
        printf("Invalid number of nodes. Must be between 1 and 50.\n");
        return 1;
    }

    printf("seed : ");
    scanf("%u", &seed);
    printf("\ncreating a BST from random numbers\n");
    srand(seed);

    treePointer root = NULL;

    printf("generating number : ");

    int tmp;
    int count = 0;
    while (count < n)
    {
        tmp = (rand() % MAX_SIZE) + 1;

        if (search(root, tmp) == NULL)
        {
            printf("%4d", tmp);
            insert(&root, tmp, tmp);
            elements[count].key = tmp;
            elements[count].item = tmp;
            count++;
        }
    }

    printf("\n");

    int searchKey;
    printf("the key to search : ");
    scanf("%d", &searchKey);

    printf("the search process : ");
    element* p = searchWithPrint(root, searchKey);
    printf("\n");

    if (p)
    {
        printf("\nthe element is in BST\n");
    }
    else
    {
        printf("\nthe element is not in BST\n");
    }

    printf("\ninorder traversal of the BST shows the sorted sequence\n");

    inorderTraversal(root);

    return 0;
}
