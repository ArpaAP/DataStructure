#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} node;

typedef struct {
    int count;
    nodePointer link;
} hdnodes;

hdnodes graph[MAX_VERTICES];

void topSort(hdnodes graph[], int n)
{
    int stack[MAX_VERTICES];
    int top = -1;
    int processed = 0;

    for (int i = 0; i < n; i++)
    {
        if (graph[i].count == 0)
        {
            stack[++top] = i;
        }
    }

    while (top != -1)
    {
        int j = stack[top--];
        printf("%d", j);

		if (processed < n - 1)
		{
			printf(" -> ");
		}

        processed++;

        nodePointer ptr;
        for (ptr = graph[j].link; ptr; ptr = ptr->link)
        {
            int k = ptr->vertex;
            graph[k].count--;
            if (graph[k].count == 0)
            {
                stack[++top] = k;
            }
        }
    }

    if (processed != n)
    {
        printf("\nGraph has a cycle\n");
        exit(1);
    }
}

int main()
{
    FILE* f;

    f = fopen("input.txt", "r");

    if (f == NULL)
    {
        printf("Cannot open file input.txt\n");
        return 1;
    }

    int n;
    fscanf(f, "%d", &n);

    int u, v;
    nodePointer temp;

    for (int i = 0; i < n; i++)
    {
        graph[i].count = 0;
        graph[i].link = NULL;
    }

    while (fscanf(f, "%d %d", &u, &v) != EOF)
    {
        temp = (nodePointer)malloc(sizeof(node));
        temp->vertex = v;
        temp->link = graph[u].link;
        graph[u].link = temp;
        graph[v].count++;
    }

    fclose(f);

    topSort(graph, n);

    return 0;
}
