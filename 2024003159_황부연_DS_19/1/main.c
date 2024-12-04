#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VERTICES 100
#define INF 999

int weight[MAX_VERTICES][MAX_VERTICES];

int distance[MAX_VERTICES];
short int found[MAX_VERTICES];
int path[MAX_VERTICES];

int choose(int distance[], int n, short int found[])
{
	int i, min, minpos;

	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++)
	{
		if (distance[i] < min && !found[i])
		{
			min = distance[i];
			minpos = i;
		}
	}

	return minpos;
}

void printDistance(int u, int distance[], int n)
{
	printf("%d : ", u);
	for (int i = 0; i < n; i++)
	{
		printf("%5d ", distance[i]);
	}
	printf("\n");
}

void shortestPath(int v, int cost[][MAX_VERTICES], int distance[], int n, short int found[])
{
	int i, u = 0, w;

	for (i = 0; i < n; i++)
	{
		distance[i] = cost[v][i];
		found[i] = 0;
		path[i] = v;
	}

	found[v] = 1;
	distance[v] = 0;

	for (i = 0; i < n - 2; i++)
	{
		printDistance(u, distance, n);

		u = choose(distance, n, found);
		found[u] = 1;

		for (w = 0; w < n; w++)
		{
			if (!found[w])
			{
				if (distance[u] + cost[u][w] < distance[w])
				{
					distance[w] = distance[u] + cost[u][w];
					path[w] = u;
				}
			}
		}
	}

	printDistance(u, distance, n);
}

int main()
{
    FILE* f;

    if ((f = fopen("input.txt", "r")) == NULL)
    {
        fprintf(stderr, "file open error\n");
        exit(EXIT_FAILURE);
    }

    int vertices, edges;

    fscanf(f, "%d %d", &vertices, &edges);

    int u, v, w;

	for (int i = 0; i < vertices; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			weight[i][j] = INF;
		}
	}

	for (int i = 0; i < edges; i++)
	{
		fscanf(f, "%d %d %d", &u, &v, &w);
		weight[u][v] = w;
		weight[v][u] = w;
	}

	fclose(f);

    shortestPath(0, weight, distance, vertices, found);

	printf("\n");
	for (int i = 1; i < vertices; i++)
	{
		printf("distance[0-%d]=%d : ", i, distance[i]);

		int path_nodes[MAX_VERTICES];
		int count = 0;
		int j = i;

		while (j != 0)
		{
			path_nodes[count++] = j;
			j = path[j];
		}
		path_nodes[count++] = 0;

		for (int k = count - 1; k > 0; k--)
		{
			printf("<%d->%d> ", path_nodes[k], path_nodes[k - 1]);
		}

		printf("\n");
	}



    return 0;
}