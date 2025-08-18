#include "mintree.h"

typedef struct Boruvka_ctx
{
	PathNode 	**ps;
	EdgeNode	*T;
	int 		*M;
	int 		m_count;
	Min_E		min;
	int 		one_based;
}				Boruvka_ctx;

static void boruvka_free(int n, Boruvka_ctx *ctx)
{
	if (ctx->ps)
		free_pathnode_array(ctx->ps, n);
	if (ctx->T)
		free_edgenode(&(ctx->T));
	if (ctx->M)
		free_array_int(ctx->M, n);
}

/**
 * @return 0 : memory allocation error
 * @return 1 : successful
 */
static int boruvka_init(Boruvka_ctx *ctx, Vertex **vs, int n, int one_based)
{
	int i;
	if (one_based != 0 && one_based != 1)
		return (printf("one_based must be 0 or 1.\n"), 0);

	ctx->ps = (PathNode **)xmalloc(sizeof(PathNode *) * n);
	ctx->M = (int *)xmalloc(sizeof(int) * n);
	if (!ctx->ps || !ctx->M)
		return (boruvka_free(n, ctx), 0);
	ctx->T = NULL;											// Alg (2-1)
	ctx->m_count = n;
	ctx->min.min_cost = DBL_MAX;
	ctx->min.min_edge = NULL;
	for (i = 0; i < n; i++)									// Alg (1)
	{
		ctx->ps[i] = create_pathnode(vs[i]);
		if (!(ctx->ps[i]))
			return (boruvka_free(n, ctx), 0);
		ctx->M[i] = 1;										// Alg (2-2)
	}
	ctx->one_based = one_based;
	return (1);
}

/**
 * @return 0 : edge is already in T
 * @return 1 : OK to append
 */
static int	partner_check(Edge *edge, EdgeNode *T)
{
	EdgeNode *node;
	int from, to;

	from = edge->from;
	to = edge->to;
	node = T;
	while(node)
	{
		if (node->edge->to == from && node->edge->from == to)
			return (0);
		node = node->next;
	}
	return (1);
}

static void	merge_node_queue(Node **queue, Vertex **vs, Boruvka_ctx *ctx)
{
	Node *node;
	Edge *edge;
	int u, v;

	node = dequeue_node(queue);
	while (node)		// supposed to be conducted while all vertices
	{
		edge = node_get_edge(node);
		u = vs[edge->from]->label;
		v = vs[edge->to]->label;							// Alg (6)
		// if (u != v)
		if (1 == 1)
		{
			if (partner_check(edge, ctx->T))
			{
				append_edgenode(&ctx->T, create_edgenode(edge));	// Alg(7)
				merge_pathnode(&ctx->ps[u], &ctx->ps[v]);	// Alg (9)
				update_labels(ctx->ps[u], u);
				ctx->M[v] = 0;
				ctx->m_count--;
			}
		}
		xfree(node, sizeof(Node));
		node = dequeue_node(queue);
	}
	print_edgenode(ctx->T, ctx->one_based);
}

void	solve_boruvka(Vertex **vs, int n, int one_based)
{
	Boruvka_ctx ctx;
	Edge *edge;
	Node *queue, *node;
	int i, j;

	if (!boruvka_init(&ctx, vs, n, one_based))
		return ;
	queue = NULL;
	while (ctx.m_count > 1)									// Alg (3)
	{
		// print_array_int(ctx.M, n, 2);
		for (i = 0; i < n; i++)
		{
			if (!ctx.M[i])									// Alg (4)
				continue;
			ctx.min.min_cost = DBL_MAX;
			ctx.min.min_edge = NULL;
			for (j = 0; j < n; j++)
			{
				if (!is_in_Vi(ctx.ps[i], j))
					continue;
				printf("[DEBUG] search an edge for i: %d, j: %d%s\n",
						i + ctx.one_based,
						j + ctx.one_based,
						ctx.one_based ? " (1-based index)" : "");
				edge = vs[j]->incidence;					// all j in con. comp. U
				while (edge)
				{
					if (!is_in_Vi(ctx.ps[i], edge->to) && (!ctx.min.min_edge || cmp_edge_cost(ctx.min.min_edge, edge) > 0))// ctx.min.min_cost > edge->cost)
					{										// Alg (5)
						ctx.min.min_cost = edge->cost;
						ctx.min.min_edge = edge;
					}
					edge = edge->next;
				}
				printf("[DEBUG] chose %d -> %d%s\n",
						ctx.min.min_edge->from + ctx.one_based,
						ctx.min.min_edge->to + ctx.one_based,
						ctx.one_based ? " (1-based index)" : "");
			}
			node = create_node(ctx.min.min_edge, NODE_TYPE_EDGE);
			if (!node)
			{
				boruvka_free(n, &ctx);
				return ;
			}
			append_node(&queue, node);
		}
		merge_node_queue(&queue, vs, &ctx);					// Alg (9)
		print_array_pathnode(ctx.ps, n, ctx.one_based);
	}
	print_edgenode(ctx.T, ctx.one_based);
	printf("is_spanning_tree: %d\n", is_spanning_tree(ctx.T, n));
	boruvka_free(n, &ctx);
}
