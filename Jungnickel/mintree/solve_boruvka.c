#include "mintree.h"

typedef struct Boruvka_ctx
{
	PathNode 	**ps;
	EdgeNode	*T;
	int 		*M;
	int 		m_count;
	Min_E		min;
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
static int boruvka_init(Vertex **vs, int n, Boruvka_ctx *ctx)
{
	int i;

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
		if (u != v)
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
}

void	solve_boruvka(Vertex **vs, int n)
{
	Boruvka_ctx ctx;
	Edge *edge;
	Node *queue, *node;
	int i, j;

	if (!boruvka_init(vs, n, &ctx))
		return ;
	print_array_pathnode(ctx.ps, n);
	printf("\n");
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
				edge = vs[j]->incidence;					// all j in con. comp. U
				while (edge)
				{
					if (!is_in_Vi(ctx.ps[i], edge->to) && ctx.min.min_cost > edge->cost)
					{										// Alg (5)
						ctx.min.min_cost = edge->cost;
						ctx.min.min_edge = edge;
					}
					edge = edge->next;
				}
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
		print_array_pathnode(ctx.ps, n);
	}
	print_edgenode(ctx.T);
	boruvka_free(n, &ctx);
}
