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
	ctx->h = heap_create(n * (n - 1) / 2, heap_cmp_edgecost);
	if (!ctx->ps || !ctx->h)
		return (kruskal_free(n, ctx), 0);
	for (i = 0; i < n; i++)
	{
		ctx->ps[i] = create_pathnode(vs[i]);
		if (!ctx->ps[i])
		{
			// free_pathnode_array(ctx->ps, i);
			kruskal_free(n, ctx);
			return (0);
		}
		edge = vs[i]->incidence;
		while (edge)
		{
			node = create_node(edge, NODE_TYPE_EDGE);
			if (!node)
			{
				free_heap_node(ctx->h, ctx->h->capacity);
				kruskal_free(n, ctx);
				return (0);
			}
			heap_push(ctx->h, node);
			edge = edge->next;
		}
	}
	ctx->T = NULL;
	return (1);
}

// void	make_queue_from_edges(Vertex **vs, int n, EdgeNode **queue)
// {
// 	int i;
// 	Edge *edge;

// 	for (i = 0; i < n; i++)
// 	{
// 		edge = vs[i]->incidence;
// 		while (edge)
// 		{
// 			append_edgenode(queue, create_edgenode(edge));
// 			edge = edge->next;
// 		}
// 	}
// }

void	solve_kruskal(Vertex **vs, int n)
{
	// EdgeNode *cur;
	PathNode *node;
	Node *cur;
	Edge *edge;
	Kruskal_ctx ctx;

	int u, v;
	if (!kruskal_init(vs, n, &ctx))
		return ;

	// print_edgenode(queue);

	// cur = edgenode_pop_first(&queue);
	// while (cur)
	while (ctx.h->size > 0)
	{
		cur = heap_pop(ctx.h);
		if (!cur)
		{
			printf("[ERROR] heap_pop return NULL unexpectedly.\n");
			break;
		}

		edge = node_get_edge(cur);
		u = vs[edge->from]->label;
		v = vs[edge->to]->label;
		// printf("%d is in %d and %d is in %d\n",
				// edge->from, u, edge->to, v);
		if (u != v)
		{
			printf("[DEBUG] merging %d and %d\n", u, v);
			merge_pathnode(&ctx.ps[u], &ctx.ps[v]);
			// printf("successfully merged.\n");
			node = ctx.ps[u];
			while (node)
			{
				// printf("node: v: %d\n", node->v->id);
				node->v->label = u;
				node = node->next;
			}
			append_edgenode(&ctx.T, create_edgenode(edge));
			// print_edgenode(T);
			print_array_pathnode(ctx.ps, n);
			// printf("added to T\n");
		}
		free_node(cur);
		if (count_edgenodes(ctx.T) == n - 1)
		{
			kruskal_free(n, &ctx);
			return ;
		}
		// cur = heap_pop(ctx.h);
	}
	// print_edgenode(T);
	// for (i = 0; i < n; i++)
	// 	free_pathnode(&ps[i]);
	// xfree(ps, sizeof(PathNode *) * n);
	// free_edgenode(&T);
}

// tidy up
