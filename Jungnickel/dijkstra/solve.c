#include "lib.h"

typedef struct Dijkstra_ctx
{
    int		**cost;
	int 	n;
	int		start;
	int 	*dist;
	int 	*prev;
	int 	*visited;
}				Dijkstra_ctx;

