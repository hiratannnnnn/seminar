#include "mintree.h"
#include "path.h"

typedef struct Kruskal_ctx
{
	Heap 		*h;
	PathNode 	**ps;
	EdgeNode 	*T;
	int			one_based;
}				Kruskal_ctx;

static void kruskal_free(int n, Kruskal_ctx *ctx)
{
	if (ctx->h)
		free_heap_node(ctx->h, ctx->h->capacity);
	if (ctx->ps)
		free_pathnode_array(ctx->ps, n);
	if (ctx->T)
		free_edgenode(&ctx->T);
}

/**
 * @return 0 : memory allocation error
 * @return 1 : successful
 */
static int kruskal_init(Kruskal_ctx *ctx, Vertex **vs, int n, int one_based)
{
	int i;
	Edge *edge;
	Node *node;
	if (one_based != 0 && one_based != 1)
		return (printf("one_based must be 0 or 1.\n"), 0);

	ctx->ps = (PathNode **)xmalloc(sizeof(PathNode *) * n);
	ctx->h = heap_create(n * (n - 1), heap_cmp_edgecost);
	if (!ctx->ps || !ctx->h)
		return (kruskal_free(n, ctx), 0);
	for (i = 0; i < n; i++)
	{
		ctx->ps[i] = create_pathnode(vs[i]);
		if (!ctx->ps[i])
			return (kruskal_free(n, ctx), 0);
		edge = vs[i]->incidence;
		while (edge)										// Alg (2)
		{
			node = create_node(edge, NODE_TYPE_EDGE);
			if (!node)
				return (kruskal_free(n, ctx), 0);
			heap_push(ctx->h, node);						// Alg (3)
			edge = edge->next;
		}
	}
	ctx->T = NULL;											// Alg (1)
	ctx->one_based = one_based;
	return (1);
}

void	solve_kruskal(Vertex **vs, int n, int one_based)
{
	PathNode *node;
	Node *cur;
	Edge *edge;
	Kruskal_ctx ctx;
	int u, v;

	if (!kruskal_init(&ctx, vs, n, one_based))
		return ;
	while (ctx.h->size > 0)									// Alg (4)
	{
		cur = heap_pop(ctx.h);								// Alg (5)
		edge = node_get_edge(cur);
		printf("edge %d -> %d%s, cost = %f\n",
				edge->from + ctx.one_based,
				edge->to + ctx.one_based,
				ctx.one_based ? " (1-based index)" : "",
				edge->cost);
		u = vs[edge->from]->label;							// Alg (6)
		v = vs[edge->to]->label;							// Alg (7)
		if (u != v)											// Alg (8)
		{
			printf("[DEBUG] merging %d and %d%s\n",
					u + ctx.one_based,
					v + ctx.one_based,
					ctx.one_based ? " (1-based index)" : "");
			merge_pathnode(&ctx.ps[u], &ctx.ps[v]);			// Alg (8-1)
			node = ctx.ps[u];
			while (node)
			{
				node->v->label = u;
				node = node->next;
			}
			append_edgenode(&ctx.T, create_edgenode(edge));	// Alg (8-2)
			print_array_pathnode(ctx.ps, n, ctx.one_based);
		}
		free_node(cur);
		if (count_edgenodes(ctx.T) == n - 1)
		{
			printf("\n[Final] chosen edges are:\n");
			print_edgenode(ctx.T, ctx.one_based);
			kruskal_free(n, &ctx);
			return ;
		}
	}
}
