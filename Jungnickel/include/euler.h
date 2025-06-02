#ifndef EULER_H
# define EULER_H

# include "lib.h"

typedef struct Euler_ctx
{
    Vertex  **vs;
	int 	*degree;
    int     *visited;
    int 	start;
    PathNode *head;
}				Euler_ctx;

// algo_euler.c
void		algo_euler		(Vertex **vs, int n, int s, Node **K);

int		make_eulerian(int **matrix, int n, double edge_ratio);

// utils_euler.c

#endif
