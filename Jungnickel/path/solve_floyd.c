#include "path.h"

typedef struct
{
	double **dist;
}			Floyd_ctx;

static void	floyd_free(Floyd_ctx *ctx, int r, int c)
{
	if (ctx->dist)
		free_matrix_double(ctx->dist, r, c);
}

static int	floyd_init(Floyd_ctx *ctx, double **cost, int n)
{
	int i, j;

	ctx->dist = (double **)xmalloc(sizeof(double *) * n);
	if (!ctx->dist)
		return (0);
	for (i = 0; i < n; i++)
	{
		ctx->dist[i] = (double *)xmalloc(sizeof(double) * n);
		if (!ctx->dist[i])
			return (floyd_free(ctx, n, i), 0);
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			ctx->dist[i][j] = cost[i][j];
	return (1);
}

void	solve_floyd(double **cost, int n)
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
				ctx.dist[i][j] = min_double(ctx.dist[i][j],
					ctx.dist[i][k] + ctx.dist[k][j]);
			}
		}
	}
	print_matrix_double(ctx.dist, n, n, 3);
	floyd_free(&ctx, n, n);
}

double 	**solve_floyd_d(double **cost, int n)
{
	Floyd_ctx ctx;
	int i, j, k;

	if (!floyd_init(&ctx, cost, n))
		return NULL;
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				ctx.dist[i][j] = min_double(ctx.dist[i][j],
					ctx.dist[i][k] + ctx.dist[k][j]);
			}
		}
	}
	print_matrix_double(ctx.dist, n, n, 3);
	// floyd_free(&ctx, n, n);
	return ctx.dist;
}
