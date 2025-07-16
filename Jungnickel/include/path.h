#ifndef PATH_H
# define PATH_H

# include "lib.h"

void 	solve_bfs	(Vertex **vs, int s, int n);

void	solve_bipart(Vertex **vs, int s, int n);

void    solve_dijkstra(Vertex **vs, int s, int n);

void solve_dijkstraPQ(Vertex **vs, int s, int n);

void	solve_bellford(Vertex **vs, int s, int n);

void	solve_floyd(int **cost, int n);

void	solve_negacycle(int **cost, int n);


#include "path.h"

typedef int (*HeapCmp)(const void *a, const void *b);

typedef struct
{
    void **array;
    int size;
    int capacity;
    HeapCmp cmp;
}       Heap;

Heap *heap_create(int capacity, HeapCmp cmp);
void heap_push(Heap *h, void *item);
void *heap_pop(Heap *h);
void    heap_free(Heap *h, int capacity);


#endif
