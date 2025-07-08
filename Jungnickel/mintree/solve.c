#include "mintree.h"

void	solve(Vertex **vs, int n)
{
	PathNode **ps;
	EdgeNode **es;
	int i;
	int k;
	int u, v;
	Edge *edge;
	EdgeNode *node;
	Min_E min;

	ps = (PathNode **)xmalloc(sizeof(PathNode *) * n);
	es = (EdgeNode **)xmalloc(sizeof(EdgeNode *) * n);
	for (i = 0; i < n; i++)
	{
		ps[i] = create_pathnode(vs[i]);
		es[i] = NULL;
	}
	for (k = 0; k < n - 1; k++)
	{
		min.min_cost = DBL_MAX;
		min.min_edge = NULL;
		for (i = 0; i < n; i++)
		{
			if (ps[i])
				break;
		}
		printf("[DEBUG] i = %d\n", i);
		if (i == n)
		{
			printf("something wrong ;;\n");
			return ;
		}
		min.min_cost = DBL_MAX;
		for (u = 0; u < n; u++)
		{
			// printf("koko\n");
			if (!is_in_Vi(ps[i], u))
				continue;
			printf("[DEBUG] u = %d\n", u);
			edge = vs[u]->incidence;
			while (edge)
			{
				if (!is_in_Vi(ps[i], edge->to))
				{
					if (edge->cost < min.min_cost)
					{
						printf("[DEBUG] updated min_cost: %f\n", edge->cost);
						printf("[DEBUG] which is %d -> %d\n", edge->from, edge->to);
						min.min_cost = edge->cost;
						min.min_edge = edge;
					}
				}
				edge = edge->next;
			}
		}
		printf("[DEBUG] search for Vj which includes %d\n", min.min_edge->to);
		for (v = 0; v < n; v++)
			if (is_in_Vi(ps[v], min.min_edge->to))
				break;
		printf("[DEBUG] %d is in %d\n", min.min_edge->to, v);
		merge_pathnode(&ps[i], &ps[min.min_edge->to]);
		merge_edgenode(&es[i], &es[min.min_edge->to]);
		node = create_edgenode(min.min_edge);
		append_edgenode(&es[i], node);
	}
	print_edgenode(es[i]);
	free_edgenode(&es[i]);
	free_pathnode(&ps[i]);
	xfree(ps, sizeof(PathNode *) * n);
	xfree(es, sizeof(EdgeNode *) * n);
}
