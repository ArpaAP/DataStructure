#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* nodePointer;
typedef struct node {
    int vertex;
    nodePointer link;
} node;

typedef struct queue* queuePointer;
typedef struct queue {
	int vertex;
	queuePointer link;
} queue;

queuePointer front, rear;

void addQueue(int vertex)
{
	queuePointer tmp = (queuePointer)malloc(sizeof(queue));
	tmp->vertex = vertex;
	tmp->link = NULL;

	if (front) rear->link = tmp;
	else front = tmp;
	rear = tmp;
}

int deleteQueue()
{
	queuePointer tmp = front;
	int vertex;

	if (!front)
	{
		fprintf(stderr, "Queue is empty\n");
		exit(EXIT_FAILURE);
	}

	vertex = front->vertex;
	front = front->link;
	free(tmp);

	return vertex;
}

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

void bfs(int v, int n, nodePointer graph[], short visited[])
{
	nodePointer w;
	front = rear = NULL;

    printf("%3d", v);

	visited[v] = 1;

	addQueue(v);
	while (front)
	{
		v = deleteQueue();
		for (w = graph[v]; w; w = w->link)
		{
			if (!visited[w->vertex])
			{
				printf("%3d", w->vertex);
				addQueue(w->vertex);
				visited[w->vertex] = 1;
			}
		}
	}
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

    printf("\n<<<<<<<<<< Breadth First Search >>>>>>>>>>\n");
    for (int i = 0; i < vertices; i++)
    {
        for (int i = 0; i < vertices; i++)
        {
            visited[i] = 0;
        }

        printf("bfs<%d> : ", i);
        bfs(i, vertices, graph, visited);
        printf("\n");
    }
    return 0;
}