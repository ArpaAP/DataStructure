#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF 1000000

typedef struct {
    int key;
    int vertex;
} element;

typedef struct {
    element heap[MAX_VERTICES];
    int heap_size;
} HeapType;

// 힙 초기화
void init_heap(HeapType* h) {
    h->heap_size = 0;
}

// 최소 힙에 원소 삽입
void insert_min_heap(HeapType* h, element item) {
    int i = ++(h->heap_size);

    while ((i != 1) && (item.key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

// 최소 힙에서 최소 원소 삭제
element delete_min_heap(HeapType* h) {
    int parent = 1, child = 2;
    element item = h->heap[1];
    element temp = h->heap[(h->heap_size)--];

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
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

// Prim 알고리즘 구현
int prim(int n, int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start) {
    int total_cost = 0;
    int d;

    int selected[MAX_VERTICES] = { 0 };
    int distance[MAX_VERTICES];
    int parent[MAX_VERTICES];

    HeapType h;
    init_heap(&h);

    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        parent[i] = -1;
    }

    distance[start] = 0;
    element start_vertex = { 0, start };
    insert_min_heap(&h, start_vertex);

    while (h.heap_size > 0) {
        element u = delete_min_heap(&h);
        int u_vertex = u.vertex;

        if (selected[u_vertex])
            continue;

        selected[u_vertex] = 1;

        for (int v = 0; v < n; v++) {
            if (adj_matrix[u_vertex][v] != INF && !selected[v] && adj_matrix[u_vertex][v] < distance[v]) {
                distance[v] = adj_matrix[u_vertex][v];
                parent[v] = u_vertex;
                element new_vertex = { distance[v], v };
                insert_min_heap(&h, new_vertex);
            }
        }

        printf("선택 vertex : %d,   ", u_vertex);
        printf("distance : ");

        for (int i = 0; i < n; i++) {
            if (distance[i] == INF) printf("  INF");
            else printf("%5d", distance[i]);
        }

        if (parent[u_vertex] != -1)
        {
            d = adj_matrix[parent[u_vertex]][u_vertex];
            printf("    선택 edge : ");
            printf("(%d, %d) distance : %d", parent[u_vertex], u_vertex, d);

            total_cost += d;
        }
        printf("\n");
    }

	return total_cost;
}

int main() {
    FILE* f;
    if ((f = fopen("input.txt", "r")) == NULL) {
        fprintf(stderr, "file open error\n");
        exit(EXIT_FAILURE);
    }

    int edges;
    fscanf(f, "%d", &edges);

    int u, v, weight;
    int max_vertex = -1;

    // 최대 정점 번호를 찾기 위한 첫 번째 패스
    int edge_list[MAX_VERTICES][3];
    for (int i = 0; i < edges; i++) {
        fscanf(f, "%d %d %d", &u, &v, &weight);
        edge_list[i][0] = u;
        edge_list[i][1] = v;
        edge_list[i][2] = weight;
        if (u > max_vertex) max_vertex = u;
        if (v > max_vertex) max_vertex = v;
    }

    int n = max_vertex + 1;

    // 인접 행렬 초기화
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj_matrix[i][j] = INF;
        }
    }

    for (int i = 0; i < edges; i++) {
        u = edge_list[i][0];
        v = edge_list[i][1];
        weight = edge_list[i][2];
        adj_matrix[u][v] = weight;
        adj_matrix[v][u] = weight;
    }

    // Prim 알고리즘 실행 (시작 정점을 0으로 설정)
    int cost = prim(n, adj_matrix, 0);

    printf("최소 비용 : %d\n", cost);

    fclose(f);
    return 0;
}
