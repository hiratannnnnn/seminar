#include		"topsort.h"

// Procedure TOPSORT (G; topnr,acyclic)
// (1) 	N ← 1, L ← ∅;
// (2) 	for i = 1 to n do ind(i) ← 0 od
// (3) 	for i = 1 to n do
// (4) 		for j ∈ Ai do ind(j) ← ind(j)+1 od
// (5) 	od
// (6) 	for i = 1 to n do if ind(i)=0 then append i to L fi od
// (7) 	while L = ∅ do
// (8) 		delete the first vertex v from L;
// (9) 		topnr(v) ← N; N ← N + 1;
// (10) 	for w ∈ Av do
// (11) 		ind(w) ← ind(w) − 1;
// (12) 		if ind(w)=0 then append w to L fi
// (13) 	od
// (14) od
// (15)	if N = n + 1 then acyclic ← true else acyclic ← false f

/**
 * @brief determines if the given graph is DAG, and finds a topological sorting if so.
 *
 * @param vs Adjacency List of all n vertices
 * @param n  size of V
 * @param topnr Pointer to a int array size of n
 */

int		topsort(Vertex **vs, int n, int *topnr)
{
	int 	*ind;
	int 	i, N;
	PathNode *head;
	PathNode *node;
	PathNode *next;
	Edge	*edge;

	ind = xcalloc(n, sizeof(int));
	if (!ind)
		return -1;
	N = 0;
	compute_degrees_from_list(vs, n, ind);
	printf("ind:");
	print_array_int(ind, n, 2);

	head = NULL;

	for (i = 0; i < n; i++)
	{
		if (ind[i] == 0)
		{
			node = create_pathnode(vs[i]);
			if (!node)
			{
				free_pathnode(&head);
				free_array_int(ind, n);
				return -1;
			}
			append_pathnode(&head, node);
		}
	}
	while (head)
	{
		node = pathnode_pop_first(&head);
		printf("looking at: %d\n", node->v->id);
		topnr[node->v->id] = N++;
		edge = vs[node->v->id]->incidence;
		while (edge)
		{
			ind[edge->to]--;
			if (ind[edge->to] == 0)
			{
				next = create_pathnode(vs[edge->to]);
				if (!next)
				{
					xfree(node, sizeof(PathNode));
					free_array_int(ind, n);
					free_pathnode(&head);
					return -1;
				}
				append_pathnode(&head, next);
			}
			edge = edge->next;
		}
		xfree(node, sizeof(PathNode));
	}

	free_pathnode(&head);
	free_array_int(ind, n);
	return (N == n);
}
