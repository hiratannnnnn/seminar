#include "path.h"

typedef struct
{
	int **dist;
}			Floyd_ctx;

static void	floyd_free(Floyd_ctx *ctx, int r, int c)
{
	if (ctx->dist)
		free_matrix_int(ctx->dist, r, c);
}

static int	floyd_init(Floyd_ctx *ctx, int **cost, int n)
{
	int i, j;

	ctx->dist = (int **)xmalloc(sizeof(int *) * n);
	if (!ctx->dist)
		return (0);
	for (i = 0; i < n; i++)
	{
		ctx->dist[i] = (int *)xmalloc(sizeof(int) * n);
		if (!ctx->dist[i])
			return (floyd_free(ctx, n, i), 0);
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			ctx->dist[i][j] = cost[i][j];
	return (1);
}

void	solve_floyd(int **cost, int n)
{
	Floyd_ctx ctx;
	int i, j, k;

	if (!floyd_init(&ctx, cost, n))
		return ;
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				ctx.dist[i][j] = min_int(ctx.dist[i][j],
					ctx.dist[i][k] + ctx.dist[k][j]);
			}
		}
	}
	print_matrix_int(ctx.dist, n, n);
	floyd_free(&ctx, n, n);
}
