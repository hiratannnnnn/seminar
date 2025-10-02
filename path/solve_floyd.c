#include "path.h"

typedef struct
{
	double **dist;
	int **pred;
}			Floyd_ctx;

static void	floyd_free(Floyd_ctx *ctx, int r, int c)
{
	if (ctx->dist)
		free_matrix_double(ctx->dist, r, c);
	if (ctx->pred)
		free_matrix_int(ctx->pred, r, c);
}

static int	floyd_init(Floyd_ctx *ctx, double **cost, int n)
{
	int i, j;

	ctx->dist = gen_matrix_double(n, n);
	ctx->pred = gen_matrix_int(n, n);
	if (!ctx->dist || !ctx->pred)
		return (0);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			ctx->dist[i][j] = cost[i][j];
			if (i == j)
				ctx->pred[i][j] = -1;
			else if (cost[i][j] < DBL_MAX / 2)
				ctx->pred[i][j] = i;
			else
				ctx->pred[i][j] = -1;
		}
	}
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
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				ctx.dist[i][j] = min_double(ctx.dist[i][j],
					ctx.dist[i][k] + ctx.dist[k][j]);
	// print_matrix_double(ctx.dist, n, n, 3);
	// floyd_free(&ctx, n, n);
	return ctx.dist;
}

void	solve_floyd_dy(double **cost, double ***dist, int ***pred, int n)
{
	Floyd_ctx ctx;
	int i, j, k;
	double new_dist;

	if (!floyd_init(&ctx, cost, n))
		return ;
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				new_dist = ctx.dist[i][k] + ctx.dist[k][j];
				if (ctx.dist[i][j] > new_dist)
				{
					ctx.dist[i][j] = new_dist;
					ctx.pred[i][j] = ctx.pred[k][j];
				}
			}
		}
	}
	*pred = ctx.pred;
	*dist = ctx.dist;
}
