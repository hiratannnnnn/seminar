#include "mintree.h"

typedef struct	PrimInfo
{
	double 	min_cost;
	Edge 	*edge;
}				PrimInfo;

void	solve_prim(Vertex **vs, int n)
{
	PrimInfo *g;
	PathNode *S, *node;
	EdgeNode *T;
	Edge *edge;
	int i;
	Min_V min;

	g = (PrimInfo *)xmalloc(sizeof(PrimInfo) * n);
	S = NULL;
	T = NULL;
	g[0].min_cost = 0.0;
	g[0].edge = NULL;
	for (i = 1; i < n; i++)
	{
		g[i].min_cost = DBL_MAX;
		g[i].edge = NULL;
	}
	while (count_pathnodes(S) < n)
	{
		printf("[DEBUG] current S is %d length\n", (int)count_pathnodes(S));
		min.min_cost = DBL_MAX;
		min.v = NULL;
		for (i = 0; i < n; i++)
		{
			if (!is_in_Vi(S, i) && g[i].min_cost < min.min_cost)
			{
				printf("[DEBUG] update min to %d which g[i] is %f\n", i, g[i].min_cost);
				min.min_cost = g[i].min_cost;
				min.v = vs[i];
			}
		}
		printf("[DEBUG] merge S and %d\n", min.v->id);
		node = create_pathnode(vs[min.v->id]);
		append_pathnode(&S, node);
		print_pathnode(S);
		if (node->v->id != 0)
		{
			printf("[DEBUG] adding edge");
			append_edgenode(&T, create_edgenode(g[min.v->id].edge));
		}

		edge = min.v->incidence;
		while (edge)
		{
			if (!is_in_Vi(S, edge->to) && g[edge->to].min_cost > edge->cost)
			{
				g[edge->to].min_cost = edge->cost;
				g[edge->to].edge = edge;
			}
			edge = edge->next;
		}
	}
	print_edgenode(T);
	xfree(g, sizeof(PrimInfo) * n);
	free_pathnode(&S);
	free_edgenode(&T);
}
