#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
    int vertex1, vertex2;
    nodePointer link1, link2;
} node;

nodePointer createNode(int v1, int v2)
{
    nodePointer p = (nodePointer)malloc(sizeof(node));
    p->vertex1 = v1;
    p->vertex2 = v2;
    p->link1 = NULL;
    p->link2 = NULL;

    return p;
}

void appendNode(nodePointer* adjLists, int v, nodePointer p)
{
    if (adjLists[v] == NULL)
    {
        adjLists[v] = p;
    }
    else
    {
        nodePointer temp = adjLists[v];
        while (1)
        {
            if (temp->vertex1 == v)
            {
                if (temp->link1 == NULL)
                {
                    temp->link1 = p;
                    break;
                }
                else
                {
                    temp = temp->link1;
                }
            }
            else
            {
                if (temp->link2 == NULL)
                {
                    temp->link2 = p;
                    break;
                }
                else
                {
                    temp = temp->link2;
                }
            }
        }
    }
}

void printEdgesOfVertex(nodePointer* adjLists, int v)
{
    nodePointer p = adjLists[v];

    while (p != NULL)
    {
        printf("(%d, %d) ", p->vertex1, p->vertex2);

        if (p->vertex1 == v) p = p->link1;
        else p = p->link2;
    }
    printf("\n");
}

void printEdgesOfVertexHeadFirst(nodePointer* adjLists, int v)
{
    nodePointer p = adjLists[v];

    while (p != NULL)
    {
        if (v == p->vertex1)
            printf("(%d, %d) ", p->vertex1, p->vertex2);
        else
            printf("(%d, %d) ", p->vertex2, p->vertex1);

        if (p->vertex1 == v) p = p->link1;
        else p = p->link2;
    }
    printf("\n");
}

int main(void)
{
    FILE* f;

    if ((f = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "file open error\n");
        return 1;
    }

    int vertices, edges;

    fscanf(f, "%d %d", &vertices, &edges);

    nodePointer* adjLists = (nodePointer*)malloc(sizeof(nodePointer) * vertices);

    for (int i = 0; i < vertices; i++)
    {
        adjLists[i] = NULL;
    }

    int v1, v2;
    nodePointer p;
    for (int i = 0; i < edges; i++)
    {
        fscanf(f, "%d %d", &v1, &v2);

        p = createNode(v1, v2);

        appendNode(adjLists, v1, p);
        appendNode(adjLists, v2, p);
    }

    printf("<<<<<<<<<<<<< edges incident to each vertex >>>>>>>>>>>>\n");

    // 첫 번째 출력: 입력 데이터 순서대로
    printf("\n간선의 정점 출력 순서 - 입력데이터 순서대로\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("edges incident to vertex %d : ", i);
        printEdgesOfVertex(adjLists, i);
    }

    // 두 번째 출력: 헤더 노드 정점이 먼저 오게
    printf("\n간선의 정점 출력 순서 - 헤더노드 정점이 먼저 오게\n");
    for (int i = 0; i < vertices; i++)
    {
        printf("edges incident to vertex %d : ", i);
        printEdgesOfVertexHeadFirst(adjLists, i);
    }

    return 0;
}
