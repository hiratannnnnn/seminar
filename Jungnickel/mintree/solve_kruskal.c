#include "mintree.h"
#include "path.h"

typedef struct Kruskal_ctx
{
	Heap 		*h;
	PathNode 	**ps;
	EdgeNode 	*T;
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
static int kruskal_init(Vertex **vs, int n, Kruskal_ctx *ctx)
{
	int i;
	Edge *edge;
	Node *node;

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
		while (edge)
		{
			node = create_node(edge, NODE_TYPE_EDGE);
			if (!node)
				return (kruskal_free(n, ctx), 0);
			heap_push(ctx->h, node);
			edge = edge->next;
		}
	}
	ctx->T = NULL;
	return (1);
}

void	solve_kruskal(Vertex **vs, int n)
{
	PathNode *node;
	Node *cur;
	Edge *edge;
	Kruskal_ctx ctx;
	int u, v;

	if (!kruskal_init(vs, n, &ctx))
		return ;
	while (ctx.h->size > 0)
	{
		cur = heap_pop(ctx.h);
		edge = node_get_edge(cur);
		u = vs[edge->from]->label;
		v = vs[edge->to]->label;
		if (u != v)
		{
			printf("[DEBUG] merging %d and %d\n", u, v);
			merge_pathnode(&ctx.ps[u], &ctx.ps[v]);
			node = ctx.ps[u];
			while (node)
			{
				node->v->label = u;
				node = node->next;
			}
			append_edgenode(&ctx.T, create_edgenode(edge));
			print_array_pathnode(ctx.ps, n);
		}
		free_node(cur);
		if (count_edgenodes(ctx.T) == n - 1)
		{
			kruskal_free(n, &ctx);
			return ;
		}
	}
}
