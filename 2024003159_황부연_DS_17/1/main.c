#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} node;

nodePointer createNode(int vertex)
{
    nodePointer tmp = (nodePointer)malloc(sizeof(node));
    tmp->vertex = vertex;
    tmp->link = NULL;

    return tmp;
}

void insertFirst(nodePointer* head, int vertex)
{
    nodePointer tmp = createNode(vertex);

    if (*head) tmp->link = *head;
    *head = tmp;
}

void printList(nodePointer head)
{
    nodePointer p = head;

    while (p != NULL)
    {
        printf("%4d", p->vertex);
        p = p->link;
    }
    printf("\n");
}

void dfs(int v, int n, nodePointer graph[], short visited[])
{
    nodePointer w;

    visited[v] = 1;
    printf("%3d", v);
    for (w = graph[v]; w; w = w->link)
        if (!visited[w->vertex])
            dfs(w->vertex, n, graph, visited);
}

int main(void)
{
    FILE* f;

    if ((f = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "file open error\n");
        exit(EXIT_FAILURE);
    }

    int vertices, edges;
    fscanf(f, "%d %d", &vertices, &edges);

    nodePointer* graph = (nodePointer*)malloc(sizeof(nodePointer) * vertices);
    short* visited = (short*)malloc(sizeof(short) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        graph[i] = NULL;
    }

    int a, b;
    for (int i = 0; i < edges; i++)
    {
        fscanf(f, "%d %d", &a, &b);
        insertFirst(&graph[a], b);
        insertFirst(&graph[b], a);
    }

    fclose(f);

    printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("graph[%d] : ", i);
        printList(graph[i]);
    }

    printf("\n<<<<<<<<<< Depth First Search >>>>>>>>>>\n");
    for (int i = 0; i < vertices; i++)
    {
        for (int i = 0; i < vertices; i++)
        {
            visited[i] = 0;
        }

        printf("dfs<%d> : ", i);
        dfs(i, vertices, graph, visited);
        printf("\n");
    }
    return 0;
}