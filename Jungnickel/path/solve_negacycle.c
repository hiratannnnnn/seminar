#include "path.h"

typedef struct
{
	int		**d;
	int		**p;
	int		neg;
}		Negacycle_ctx;

static void	negacycle_free(Negacycle_ctx *ctx, int n)
{
	if (ctx->d)
		free_matrix_int(ctx->d, n, n);
	if (ctx->p)
		free_matrix_int(ctx->p, n, n);
}

static int negacycle_init(Negacycle_ctx *ctx, int **cost, int n)
{
	int i;
	int j;

	ctx->d = (int **)xmalloc(sizeof(int *) * n);
	ctx->p = (int **)xmalloc(sizeof(int *) * n);
	if (!ctx->d || !ctx->p)
		return (0);
	for (i = 0; i < n; i++)
	{
		ctx->d[i] = (int *)xmalloc(sizeof(int) * n);
		ctx->p[i] = (int *)xmalloc(sizeof(int) * n);
		if (!ctx->d[i] || !ctx->p[i])
			return (negacycle_free(ctx, n), 0);
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				ctx->d[i][j] = cost[i][j];
				ctx->p[i][j] = -1;
			}
			else if (cost[i][j] == INT_MAX / 2)
			{
				ctx->d[i][j] = INT_MAX / 2;
				ctx->p[i][j] = -1;
			}
			else
			{
				ctx->d[i][j] = cost[i][j];
				ctx->p[i][j] = i;
			}
		}
	}
	ctx->neg = 0;
	return (1);
}



void	solve_negacycle(int **cost, int n)
{
	Negacycle_ctx ctx;
	int i, j, k;

	if (!negacycle_init(&ctx, cost, n))
		return ;
	k = -1;
	while (!ctx.neg && k < n - 1)
	{
		k++;
		for (i = 0; i < n; i++)
		{
			if (ctx.d[i][k] + ctx.d[k][i] < 0)
			{
				ctx.neg = 1;
				// CYCLE;
			}
			else
			{
				for (j = 0; j < n; j++)
				{
					if (ctx.d[i][k] + ctx.d[k][j] < ctx.d[i][j])
					{
						ctx.d[i][j] = ctx.d[i][k] + ctx.d[k][j];
						ctx.p[i][j] = ctx.p[k][j];
					}
				}
			}
		}
		printf("\nk = %d\n", k);
		printf("ctx.d\n");
		print_matrix_int(ctx.d, n, n);
		printf("ctx.p\n");
		print_matrix_int(ctx.p, n, n);
		printf("ctx.neg: %d\n", ctx.neg);
	}
	negacycle_free(&ctx, n);
}
