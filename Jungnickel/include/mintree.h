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
int 		is_in_Vi			(PathNode *node, int index);
int 		is_in_Vi_label		(PathNode *node, int index);
void 		free_pathnode_array	(PathNode **ps, int n);
int 		is_spanning_tree	(EdgeNode *list, int n);


// solve.c
void		solve				(Vertex **vs, int n);

// solve_prim.c
void		solve_prim			(Vertex **vs, int s, int n);

// solve_kruskal.c
void		solve_kruskal		(Vertex **vs, int n);

// solve_boruvka.c
void		solve_boruvka		(Vertex **vs, int n);

#endif
