#include "heap.h"
#include <stdio.h>
#define HEAPSIZE 8

int main()
{
	struct heap *h;
	struct heapnode node;
	h = heap_create(HEAPSIZE);

	heap_insert(h, 3, 3);
	heap_insert(h, 8, 8);
	heap_insert(h, 9, 9);
	heap_insert(h, 25, 25);
	heap_insert(h, 13, 13);
	heap_insert(h, 5, 5);
	heap_insert(h, 0, 0);

	heap_insert(h, 3, 999);
	for (int i = 0; i < h->nnodes; i++) {
		printf("key : %d\tvalue : %d\n", h->nodes[i].key, h->nodes[i].value);
	}
	
	heap_free(h);
	return 0;
}


void ShortestPathDijkstra(struct graph *g, int src, int *d, int *prev) {
	minHeap *hp = heap_create(21);

	for (int i = 1; i < g->nvertices; i++) { // Помещаем вершины в очередь с приоритетом
	d[i] = 100000;
	prev[i] = -1;
	insertNode(hp, i, d[i]);
	}

	d[src] = 0;
	prev[src] = -1;

	insertNode(hp, src, d[src]);

	for (int i = 0; i < g->nvertices; i++) {
		extractMinNode(hp); // Извлекаем узел, ближайший к начальному
		g->visited[i] = 1; // Отмечаем v как посещённый

		for (int j = i + 1; j < g->nvertices; j++) { // Цикл по смежным непосещённым вершинам узла v
			if ((d[i] + g->m[i * g->nvertices + j] < d[j]) && (g->m[i * g->nvertices + j] > 0)) { // Путь через u короче текущего пути?
				d[j] = d[i] + g->m[i * g->nvertices + j];
				decrease_key(hp, j, d[j], 21);
				prev[j] = i + 1;
			}
		}
	}
}