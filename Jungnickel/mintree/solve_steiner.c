#include "mintree.h"
#include "path.h"

typedef struct Steiner_ctx
{
	double W;
	double **dist;
	int **pred;
	int *R_S;
	Vertex **vs;
	EdgeNode *T;

}				Steiner_ctx;

static void steiner_free(Steiner_ctx *ctx, int n)
{
	if (ctx->dist)
		free_matrix_double(ctx->dist, n, n);
	if (ctx->pred)
		free_matrix_int(ctx->pred, n, n);
	if (ctx->R_S)
		free_array_int(ctx->R_S, n);
	if (ctx->vs)
		free_vertex_array(ctx->vs, n);
	if (ctx->T)
		free_edgenode(&ctx->T);
}

static int steiner_init(Steiner_ctx *ctx, double **cost, int r, int n)
{
	int i;

	ctx->R_S = (int *)xmalloc(sizeof(int) * n);
	solve_floyd_dy(cost, &ctx->dist, &ctx->pred, n);
	if (!ctx->R_S || !ctx->dist || !ctx->pred)
		return (steiner_free(ctx, n), 0);
	ctx->vs = cost_matrix_to_vertices(ctx->dist, n, 1);
	if (!ctx->vs)
		return (steiner_free(ctx, n), 0);

	for (i = 0; i < n; i++)
		ctx->R_S[i] = (i < r);
	ctx->W = DBL_MAX;
	ctx->T = NULL;
	return (1);
}

static void print_steiner(EdgeNode *head, int **pred)
{
	int from, cur, to;
	Edge *edge;
	EdgeNode *node;

	node = head;
	while (node)
	{
		edge = node->edge;
		from = edge->from;
		to = edge->to;
		cur = pred[from][to];
		printf("%d - %d\n", cur, to);
		while (from != cur)
		{
			to = cur;
			cur = pred[from][cur];
			printf("%d - %d \n", cur, to);
		}
		node = node->next;
	}
	nl(1);
}

/**
 * @param r
 * assume the first r vertices as R
 */
void solve_steiner(double **cost, int r, int n)
{
	Steiner_ctx ctx;
	int i, j, carry;
	double cur;
	EdgeNode *node;

	if (!steiner_init(&ctx, cost, r, n))
		return ;
	for (i = 0; i < pow(2, n - r); i++)
	{
		carry = i;
		for (j = r; j < n; j++)
		{
			ctx.R_S[j] = carry % 2;
			carry = carry / 2;
		}
		if (sum_array(ctx.R_S, n) <= r + r - 2)
		{
			reset_labels(ctx.vs, n);
			solve_prim_steiner(ctx.vs, n, ctx.R_S, &node, &cur);
			if (cur < ctx.W)
			{
				ctx.W = cur;
				free_edgenode(&ctx.T);
				ctx.T = node;
				node = NULL;
			}
			else
				free_edgenode(&node);
		}
	}
	print_edgenode(ctx.T, 0);
	print_steiner(ctx.T, ctx.pred);
	steiner_free(&ctx, n);
}
