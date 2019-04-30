#include "graph.h"
#include <sys/time.h>
#include <time.h>
#include <math.h> 

#define CON_GRAPH_SIZE 20
#define LAT_GRAPH_SIZE 9

int getrand(int min, int max);
double wtime();

int main()
{
	srand(time(NULL));
    
    struct graph* g = graph_create(CON_GRAPH_SIZE);

    int d[CON_GRAPH_SIZE];
    int prev[CON_GRAPH_SIZE];
    int path[CON_GRAPH_SIZE];

	// граф уже связный
	for (int i = 1; i < CON_GRAPH_SIZE; i++) {
		graph_set_edge(g, i, i + 1, getrand(1, 10));
	}
	// Рандомом соединить вершины
    int a, b;
    for (int i = 1; i < CON_GRAPH_SIZE * getrand(2, 7); i++) {
        a = rand() % (CON_GRAPH_SIZE - 1);
        b = rand() % (CON_GRAPH_SIZE - 1);
        if (a == i || a == i + 1 || i == a + 1 || a == 0 || a == b || b == 0 || b == i + 1 || b == i - 1) {
            continue;
        }
        graph_set_edge(g, a, b, getrand(1, 10));
    } 
    
    // Вывод
    printf("CONNECTED GRAPH : \n");
    printf("   ");
    for (int k = 0; k < g->nvertices; k++) {
        printf("%2.d ", k + 1);
    }
    printf("\n");

    for (int i = 0; i < g->nvertices; i++) {
        printf("\n%2.d ", i + 1);
        for (int j = 0; j < g->nvertices; j++) {
            printf("%2.d ", g->m[i * g->nvertices + j]);
        }
        printf("\n");
    }
    
    
	double t = wtime();
	ShortestPathDijkstra(g, 1, d, prev);
	t = wtime() - t;

    
    int i, j, len;
    for (i = 1; i <= CON_GRAPH_SIZE; i++)
    {
        len = RecoveryPath(g, 1, i, path, prev);
        printf("0 >> %d = %d\n", i, d[i]);
        printf("Vertex = ");
        for (j = 1; j < len; j++)
        {
            printf("%d -> ", path[j]);
        }
        printf("%d\n\n", path[j]);
    }
   
    printf("\n");
    printf("CONNECTED GRAPH TIME : %f\n", t);
    











    struct graph* lg = graph_create(LAT_GRAPH_SIZE);

    int x = sqrt(LAT_GRAPH_SIZE);
   	for (int i = 1; i <= LAT_GRAPH_SIZE - x; i++) {
		if (i % x == 0) {
			graph_set_edge(lg, i, i + x, getrand(1, 10));
			continue;
		}
		graph_set_edge(lg, i, i + 1, getrand(1, 10));
		graph_set_edge(lg, i, i + x, getrand(1, 10));
	}
    for (int i = LAT_GRAPH_SIZE - x + 1; i < LAT_GRAPH_SIZE; i++) {
        graph_set_edge(lg, i, i + 1, getrand(1, 10));
    }

	int ld[LAT_GRAPH_SIZE];
    int lprev[LAT_GRAPH_SIZE];
    int lpath[LAT_GRAPH_SIZE];

    printf("TABLE GRAPH : \n");
    t = wtime();
    ShortestPathDijkstra(lg, 1, ld, lprev);
    t = wtime() - t;

	//Выводим граф
    printf("   ");
    for (int k = 0; k < lg->nvertices; k++) {
        printf("%2.d ", k + 1);
    }
    printf("\n");

    for (int i = 0; i < lg->nvertices; i++) {
        printf("\n%2.d ", i + 1);
        for (int j = 0; j < lg->nvertices; j++) {
            printf("%2.d ", lg->m[i * lg->nvertices + j]);
        }
        printf("\n");
    }
    

    lpath[1] = 0;
    for (int i = 1; i < lg->nvertices; i++) {
        printf("%d ", prev[i]);
    }
    printf("\n");
    for (i = 1; i <= LAT_GRAPH_SIZE; i++)
    {
        len = RecoveryPath(lg, 1, i, lpath, lprev);
        printf("0 >> %d = %d\n", i, ld[i]);
        printf("Vertex = ");
        for (j = 1; j < len; j++)
        {
            printf("%d -> ", lpath[j]);
        }
        printf("%d\n\n", lpath[j]);
    }

    printf("TABLE GRAPH TIME : %f\n", t);
    
    return 0;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}