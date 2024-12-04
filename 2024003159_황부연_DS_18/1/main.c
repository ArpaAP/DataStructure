#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100

typedef struct {
    int key;
    int u;
    int v;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

void insert_heap_edge(HeapType* h, int u, int v, int weight) {
    element e;
    e.u = u;
    e.v = v;
    e.key = weight;
    insert_min_heap(h, e);
}

int simpleFind(int i, int parent[])
{
    while (parent[i] >= 0)
        i = parent[i];
    return i;
}

void simpleUnion(int i, int j, int parent[])
{
    parent[i] = j;
}

void init(HeapType* h)
{
    h->heap_size = 0;
}

element delete_min_heap(HeapType* h)
{
    int parent, child;
    element item, temp;

    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];

    parent = 1;
    child = 2;

    while (child <= h->heap_size)
    {
        if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
            child++;

        if (temp.key <= h->heap[child].key)
            break;

        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }

    h->heap[parent] = temp;
    return item;
}

int kruskal(HeapType* h, int n, int parent[])
{
    int i = 0;
    int total_cost = 0;
    element e;

    while (i < n - 1)
    {
        e = delete_min_heap(h);

        int uset = simpleFind(e.u, parent);
        int vset = simpleFind(e.v, parent);

        if (uset != vset)
        {
            printf("(%d, %d) %d\n", e.u, e.v, e.key);
			total_cost += e.key;
            simpleUnion(uset, vset, parent);
            i++;
        }
    }

    return total_cost;
}

int main()
{
    FILE* f;
    if ((f = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "file open error\n");
        exit(EXIT_FAILURE);
    }

    int edges;
    fscanf(f, "%d", &edges);

    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    init(h);

    int u, v, weight;
    int max_vertex = -1;

    element* edge_list = (element*)malloc(sizeof(element) * edges);
    for (int i = 0; i < edges; i++)
    {
        fscanf(f, "%d %d %d", &u, &v, &weight);
        edge_list[i].u = u;
        edge_list[i].v = v;
        edge_list[i].key = weight;
        if (u > max_vertex) max_vertex = u;
        if (v > max_vertex) max_vertex = v;
    }

    int n = max_vertex + 1;

    int* parent = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        parent[i] = -1;

    for (int i = 0; i < edges; i++)
    {
        insert_heap_edge(h, edge_list[i].u, edge_list[i].v, edge_list[i].key);
    }

    free(edge_list);

    int cost = kruskal(h, n, parent);

    printf("\n최소비용 : %d\n", cost);

    free(parent);
    free(h);
    fclose(f);

    return 0;
}

