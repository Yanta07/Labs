#include "graph.h"

struct graph *graph_create(int nvertices)
{
    struct graph *g;
    g = malloc(sizeof(*g));
    g->nvertices = nvertices;
    g->visited = malloc(sizeof(int) * nvertices);
    g->m = malloc(sizeof(int) * nvertices * nvertices);
    graph_clear(g);
    return g;
};

void graph_clear(struct graph *g)
{
    int i, j;
    for (i = 0; i < g->nvertices; i++)
    {
        g->visited[i] = 0;
        for (j = 0; j < g->nvertices; j++)
        {
            g->m[i * g->nvertices + j] = 0;
        }
    }
}

void graph_free(struct graph *g)
{
    free(g->m);
    free(g);
}

void graph_set_edge(struct graph *g, int i, int j, int w)
{
    g->m[(i - 1) * g->nvertices + j - 1] = w;
    g->m[(j - 1) * g->nvertices + i - 1] = w;
}

int graph_get_edge(struct graph *g, int i, int j)
{
    return g->m[(j - 1) * g->nvertices + i - 1];
}

void ShortestPathDijkstra(struct graph *g, int  src, int *d, int *prev)
{
    struct heap *h;
    struct heapnode v;

    int i, u, w;
    h = heap_create(g->nvertices);
    // Помещаем вершины в очередь с приоритетом
    for (i = 1; i < g->nvertices + 1; i++) {
        d[i] = INT_MAX;
        prev[i] = -1;
        heap_insert(h, d[i], i);
        if (i + 1 == src) {
            i++;
        }
    }
    
    d[src] = 0;
    prev[src] = -1;
    heap_insert(h, d[src], src);

    for (i = 1; i < g->nvertices + 1; i++) {
        // Извлекаем узел, ближайший к начальному
        v = heap_extract_min(h);
        // Отмечаем вершину как посещённую
        g->visited[v.value] = 1;
        // Цикл по смежным непосещённым вершинам узла v
        for (u = 1; u < g->nvertices + 1; u++) {
            w = graph_get_edge(g, v.value, u);
            if (w == 0) {
                continue;
            }
            if (g->visited[u] > 0) {
                continue;
            }
            if ((d[v.value] + w) < d[u]) {
                d[u] = d[v.value] + w;
                heap_decrease_key(h, u, d[u]);
                prev[u] = v.value;
            }
        }
    }
}

int RecoveryPath(struct graph *g, int src, int dst, int* path, int* prev)
{
    int i, j, pathlen = 1;
    i = dst;
    while (i != src) {
        pathlen = pathlen + 1;
        i = prev[i];
    }
    j = 0;
    i = dst;
    while (i != src) {
        path[pathlen - j] = i;
        i = prev[i];
        j = j + 1;
    }
    return pathlen;
}

