#include "path.h"

typedef struct
{
	int *d;
	int *d_prev;
	int converged;
}			Bellford_ctx;

static void bellford_free(Bellford_ctx *ctx, int n)
{
	if (ctx->d)
		free_array_int(ctx->d, n);
	if (ctx->d_prev)
		free_array_int(ctx->d_prev, n);
}

static int bellford_init(Bellford_ctx *ctx, int n)
{
	int i;

	ctx->d = (int *)xmalloc(sizeof(int) * n);
	ctx->d_prev = (int *)xmalloc(sizeof(int) * n);
	if (!ctx->d || !ctx->d_prev)
	{
		bellford_free(ctx, n);
		return (0);
	}
	for (i = 0; i < n; i++)
		ctx->d[i] = ctx->d_prev[i] = INT_MAX / 2;
	ctx->converged = 0;
	return (1);
}

static void copy_array_int(int *from, int *to, int n)
{
	int i;

	for (i = 0; i < n; i++)
		to[i] = from[i];
}

void	solve_bellford(Vertex **vs, int s, int n)
{
	Bellford_ctx ctx;
	int u, v, min_dist, new_dist;
	Edge *edge;

	if (!bellford_init(&ctx, n))
		return ;
	ctx.d[s] = 0;
	do {
		copy_array_int(ctx.d, ctx.d_prev, n);
		for (v = 0; v < n; v++)
		{
			min_dist = ctx.d_prev[v];
			for (u = 0; u < n; u++)
			{
				if (u == v)
					continue;
				edge = vs[u]->incidence;
				while (edge)
				{
					if (edge->to == v)
					{
						if (ctx.d_prev[u] != INT_MAX / 2)
						{
							new_dist = ctx.d_prev[u] + edge->cost;
							if (new_dist < min_dist)
								min_dist = new_dist;
						}
					}
					edge = edge->next;
				}
			}
			ctx.d[v] = min_dist;
		}
		ctx.converged = 1;
		for (v = 0; v < n; v++)
		{
			if (ctx.d[v] != ctx.d_prev[v])
			{
				ctx.converged = 0;
				break;
			}
		}
	} while (!ctx.converged);
	print_array_int(ctx.d, n, 2);
	bellford_free(&ctx, n);
}
