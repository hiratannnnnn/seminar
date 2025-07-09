#include "mintree.h"

void	make_queue_from_edges(Vertex **vs, int n, EdgeNode **queue)
{
	int i;
	Edge *edge;

	for (i = 0; i < n; i++)
	{
		edge = vs[i]->incidence;
		while (edge)
		{
			append_edgenode(queue, create_edgenode(edge));
			edge = edge->next;
		}
	}
}

void	solve_kruskal(Vertex **vs, int n)
{
	EdgeNode *queue;
	PathNode **ps;
	EdgeNode *T;
	EdgeNode *cur;
	PathNode *node;

	int u, v, i;

	ps = (PathNode **)xmalloc(sizeof(PathNode *) * n);
	queue = NULL; T = NULL;

	for (i = 0; i < n; i++)
		ps[i] = create_pathnode(vs[i]);

	make_queue_from_edges(vs, n, &queue);
	sort_edgenode_cost(&queue, cmp_double_asc);

	print_edgenode(queue);

	printf("adsf\n");
	cur = edgenode_pop_first(&queue);
	printf("cur: %d -> %d\n", cur->edge->from, cur->edge->to);
	print_edgenode(queue);
	while (cur)
	{
		u = vs[cur->edge->from]->label;
		v = vs[cur->edge->to]->label;
		printf("%d is in %d and %d is in %d\n",
				cur->edge->from, u, cur->edge->to, v);
		if (u != v)
		{
			printf("merging %d and %d\n", u, v);
			merge_pathnode(&ps[u], &ps[v]);
			printf("adsf\n");
			node = ps[u];
			while (node)
			{
				printf("node: v: %d\n", node->v->id);
				node->v->label = u;
				node = node->next;
			}
			append_edgenode(&T, cur);
			printf("adsfasdfa\n");
		}
		cur = edgenode_pop_first(&queue);
		printf("cur: %d -> %d\n", cur->edge->from, cur->edge->to);
		// print_edgenode(queue);
	}
	print_edgenode(T);
	// for (i = 0; i < n; i++)
	// 	free_pathnode(&ps[i]);
	// xfree(ps, sizeof(PathNode *) * n);
	// free_edgenode(&T);
}
