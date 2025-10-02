#ifndef PATH_H
# define PATH_H

# include "../include/lib.h"

void 	solve_bfs	(Vertex **vs, int s, int n);

void	solve_bipart(Vertex **vs, int s, int n);

void    solve_dijkstra(Vertex **vs, int s, int n);

void 	solve_dijkstraPQ(Vertex **vs, int s, int n);

void	solve_bellford(Vertex **vs, int s, int n);

void	solve_floyd(double **cost, int n);
double 	**solve_floyd_d(double **cost, int n);
void	solve_floyd_dy(double **cost, double ***dist, int ***pred, int n);

void	solve_negacycle(int **cost, int n);

// wtf is this
#include "path.h"

Heap 	*heap_create(int capacity, HeapCmp cmp);
void 	heap_push(Heap *h, void *item);
void 	*heap_pop(Heap *h);
void    free_heap_node(Heap *h, int capacity);
void 	*heap_peek(Heap *h);
void 	heap_clear(Heap *h);
int 	heap_cmp_edgecost(const void *a, const void *b);
int 	heap_cmp_edgecost_id(const void *a, const void *b);

#endif
