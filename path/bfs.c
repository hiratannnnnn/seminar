#include "path.h"

typedef struct
{
	Node *queue;
	int *d;
}		Bfs_ctx;

static void bfs_free(Bfs_ctx *ctx, int n)
{
	free_nodes(&ctx->queue);
	free_array_int(ctx->d, n);
}

/**
 * @return 0 : error
 * @return 1 : successful
 */
static int bfs_init(Bfs_ctx *ctx, int n)
{
	int i;

	ctx->queue = NULL;
	ctx->d = (int *)xmalloc(sizeof(int) * n);
	if (!ctx->d)
	{
		bfs_free(ctx, n);
		return (0);
	}
	for (i = 0; i < n; i++)
		ctx->d[i] = -1;
	return (1);
}

void 	solve_bfs(Vertex **vs, int s, int n)
{
	Bfs_ctx ctx;
	Node *node;
	Edge *edge;

	if (!bfs_init(&ctx, n))
		return ;
	ctx.d[s] = 0;
	node = create_node(vs[s], NODE_TYPE_VERTEX);
	if (!node)
	{
		bfs_free(&ctx, n);
		return ;
	}
	enqueue_node(&ctx.queue, node);
	while (ctx.queue)
	{
		node = dequeue_node(&ctx.queue);
		edge = node_get_vertex(node)->incidence;
		free_node(node);
		while (edge)
		{
			printf("[DEBUG] edge %d -> %d\n", edge->from, edge->to);
			if (ctx.d[edge->to] == -1)
			{
				ctx.d[edge->to] = ctx.d[edge->from] + 1;
				node = create_node(vs[edge->to], NODE_TYPE_VERTEX);
				if (!node)
				{
					bfs_free(&ctx, n);
					return ;
				}
				printf("[DEBUG] created node %d\n", edge->to);
				enqueue_node(&ctx.queue, node);
			}
			edge = edge->next;
		}
	}
	print_array_int(ctx.d, n, 2);
	bfs_free(&ctx, n);
	return ;
}
