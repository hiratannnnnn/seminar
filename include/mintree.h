#ifndef MINTREE_H
# define MINTREE_H

# include "../include/lib.h"

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
int 		is_in_Vi			(PathNode *node, int index);
int 		is_in_Vi_label		(PathNode *node, int index);
void 		free_pathnode_array	(PathNode **ps, int n);
int 		is_spanning_tree	(EdgeNode *list, int n);


// solve.c
void		solve				(Vertex **vs, int n);

// solve_prim.c
void		solve_prim			(Vertex **vs, int s, int n, int one_based);
void		solve_prim_steiner	(Vertex **vs, int n, int *R_S, EdgeNode **head, double *cost);

// solve_kruskal.c
void		solve_kruskal		(Vertex **vs, int n, int one_based);

// solve_boruvka.c
void		solve_boruvka		(Vertex **vs, int n, int one_based);

// solve_steiner.c
void 		solve_steiner		(double **cost, int r, int n);

#endif
