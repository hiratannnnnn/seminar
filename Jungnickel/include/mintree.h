#ifndef MINTREE_H
# define MINTREE_H

# include "lib.h"

typedef struct Min_V
{
	double min_cost;
	Vertex *v;
}				Min_V;

typedef struct Min_E
{
	double min_cost;
	Edge *min_edge;
}				Min_E;

// utils.c
int 		is_in_Vi		(PathNode *node, int index);

// solve.c
void		solve			(Vertex **vs, int n);

// solve_prim.c
void		solve_prim		(Vertex **vs, int n);

void		solve_kruskal	(Vertex **vs, int n);

#endif
