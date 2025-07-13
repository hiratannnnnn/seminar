#include "path.h"

typedef struct
{
	Node *queue;
	int *d;
	int bip;
	PathNode *S;
	PathNode *T;
}		Bipart_ctx;

static void bipart_free(Bipart_ctx *ctx, int n)
{
	if (ctx->d)
		free_array_int(ctx->d, n);
	if (ctx->queue)
		free_nodes(&ctx->queue);
	if (ctx->S)
		free_pathnode(&ctx->S);
	if (ctx->T)
		free_pathnode(&ctx->T);
}

static int bipart_init(Bipart_ctx *ctx, int s, int n)
{
	int i;

	ctx->queue = NULL;
	ctx->d = (int *)xmalloc(sizeof(int) * n);
	ctx->bip = 1;
	ctx->S = NULL;
	ctx->T = NULL;
	if (!ctx->d)
	{
		bipart_free(ctx, n);
		return 0;
	}
	for (i = 0; i < n; i++)
		ctx->d[i] = -1;
	ctx->d[s] = 0;
	return 1;
}

void	solve_bipart(Vertex **vs, int s, int n)
{
	Bipart_ctx ctx;
	Node *node;
	Edge *edge;

	if (!bipart_init(&ctx, s, n))
		return ;
	node = create_node(vs[s], NODE_TYPE_VERTEX);
	if (!node)
	{
		bipart_free(&ctx, n);
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
			printf("[DEBUG] edge: %d -> %d, d: %d %d\n",
				edge->from, edge->to, ctx.d[edge->from], ctx.d[edge->to]);

			if (ctx.d[edge->to] == -1)
			{
				ctx.d[edge->to] = ctx.d[edge->from] + 1;
				node = create_node(vs[edge->to], NODE_TYPE_VERTEX);
				if (!node)
				{
					bipart_free(&ctx, n);
					return ;
				}
				printf("[DEBUG] created node %d\n", edge->to);
				enqueue_node(&ctx.queue, node);
			}
			else if (ctx.d[edge->from] == ctx.d[edge->to])
			{
				printf("FOUND odd length cycle!\n");
				ctx.bip = 0;
				printf("bip: %d\n", ctx.bip);
				bipart_free(&ctx, n);
				return ;
			}
			edge = edge->next;
		}
	}
	printf("bip: %d\n", ctx.bip);
	bipart_free(&ctx, n);
}
