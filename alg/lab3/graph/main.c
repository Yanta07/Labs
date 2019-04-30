#include "graph.h"
#include <stdio.h>

int main() 
{ 
	struct graph *g;
	g = graph_create(10);
	graph_set_edge(g, 1, 2, 1);
	graph_set_edge(g, 1, 4, 1);
	graph_set_edge(g, 2, 3, 1);
	graph_set_edge(g, 1, 3, 1);
	
	printf("DFS:\n");
	graph_dfs(g, 2);

	graph_free(g);
	return 0;
}

