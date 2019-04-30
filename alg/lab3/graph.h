#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct graph {
	int nvertices; // Число вершин
	int *m; // Матрица n x n
	int *visited;
};

struct graph *graph_create(int nvertices);
void graph_clear(struct graph *g);
void graph_free(struct graph *g);
void graph_set_edge(struct graph *g, int i, int j, int w);
int graph_get_edge(struct graph *g, int i, int j);
void ShortestPathDijkstra(struct graph *g, int  src, int *d, int *prev);
int RecoveryPath(struct graph *g, int  src, int dst, int* path, int* prev);
