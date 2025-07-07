#include "mintree.h"

typedef struct Min
{
	double min_cost;
	Edge *min_edge;
}				Min;

static int is_in_Vi(PathNode *node, int index)
{
	PathNode *cur;

	cur = node;
	while (cur)
	{
		// printf("[DEBUG] searching for %d\n", index);
		if (cur->v->id == index)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static void merge_pathnode(PathNode **ps, int i, Min *min)
{
	PathNode *i_last;
	int v;
	v = min->min_edge->to;

	printf("merge %d and %d\n", i, v);
	i_last = get_last_pathnode(ps[i]);
	printf("%p\n", i_last);
	ps[v]->prev = i_last;
	i_last->next = ps[v];
	ps[v] = NULL;
	print_pathnode(ps[i]);
}

static void merge_edgenode(EdgeNode **es, int i, Min *min)
{
	EdgeNode *node;
	EdgeNode *i_last;
	EdgeNode *v_head;
	int v;
	v = min->min_edge->to;
	Edge *edge;
	edge = min->min_edge;

	node = create_edgenode(edge);
	i_last = get_last_edgenode(es[i]);
	v_head = es[v];
	if (i_last)
	{
		i_last->next = v_head;
		if (v_head)
			v_head->prev = i_last;
	}
	else
		es[i] = v_head;
	es[v] = NULL;
	append_edgenode(&es[i], node);
}

void	solve(Vertex **vs, int n)
{
	PathNode **ps;
	EdgeNode **es;
	int i;
	int k;
	int u, v;
	Edge *edge;
	Min min;

	ps = (PathNode **)xmalloc(sizeof(PathNode *) * n);
	es = (EdgeNode **)xmalloc(sizeof(EdgeNode *) * n);
	for (i = 0; i < n; i++)
	{
		ps[i] = create_pathnode(vs[i]);
		es[i] = NULL;
	}
	// printf("ps[0]: %d\n", ps[0]->v->id);
	// printf("ps[0]->next: %p\n", ps[0]->next);
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
		merge_pathnode(ps, i, &min);
		merge_edgenode(es, i, &min);
	}
	print_edgenode(es[i]);
	free_edgenode(&es[i]);
	free_pathnode(&ps[i]);
	xfree(ps, sizeof(PathNode *) * n);
	xfree(es, sizeof(EdgeNode *) * n);
}
