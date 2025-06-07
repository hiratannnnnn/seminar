#include "bipartite.h"

typedef struct 	Hungarian_ctx
{
	int 	n;
	double 	*u;
	double 	*v;
	int 	*p;
	int 	*way;
	double 	*minv;
	int 	*used;
}				Hungarian_ctx;

static void free_hungarian_ctx(Hungarian_ctx *ctx)
{
    if (ctx->u)
        free_array_double(ctx->u, ctx->n + 1);
    if (ctx->v)
        free_array_double(ctx->v, ctx->n + 1);
    if (ctx->p)
        free_array_int(ctx->p, ctx->n + 1);
    if (ctx->way)
        free_array_int(ctx->way, ctx->n + 1);
    if (ctx->minv)
        free_array_double(ctx->minv, ctx->n + 1);
    if (ctx->used)
        free_array_int(ctx->used, ctx->n + 1);
}

static int	init_hungarian_ctx(Hungarian_ctx *ctx, int n)
{
    ctx->n 		= n;
    ctx->u 		= (double 	*)	xcalloc(n + 1, sizeof(double));
    ctx->v 		= (double 	*)	xcalloc(n + 1, sizeof(double));
    ctx->p		= (int 		*)	xcalloc(n + 1, sizeof(int));
    ctx->way 	= (int 		*)	xcalloc(n + 1, sizeof(int));
    ctx->minv 	= (double 	*)	xcalloc(n + 1, sizeof(double));
    ctx->used 	= (int 		*)	xcalloc(n + 1, sizeof(int));
    if (!ctx->u || !ctx->v || !ctx->p || !ctx->way || !ctx->minv || !ctx->used)
    {
        free_hungarian_ctx(ctx);
        return (0);
    }
    return (1);
}

void	free_array_double(double *arr, int n)
{
	if (!arr)
		return ;
	xfree(arr, sizeof(double) * n);
}

static void init_row(Hungarian_ctx *ctx)
{
    int j;

    for (j = 0; j <= ctx->n; j++)
    {
        ctx->minv[j] = DBL_MAX;
        ctx->used[j] = 0;
    }
}

static void find_min(Hungarian_ctx *ctx, double *delta, int *j1)
{
    int j;

    *delta = DBL_MAX;
    *j1 = 0;
    for (j = 1; j <= ctx->n; j++)
    {
        if (!ctx->used[j] && ctx->minv[j] < *delta)
        {
            *delta = ctx->minv[j];
            *j1 = j;
        }
    }
}

static void update_labels(Hungarian_ctx *ctx, double delta)
{
    int j;

    for (j = 0; j <= ctx->n; j++)
    {
        if (ctx->used[j])
        {
            ctx->u[ctx->p[j]] += delta;
            ctx->v[j] -= delta;
        }
        else
            ctx->minv[j] -= delta;
    }
}

static void augment_path(Hungarian_ctx *ctx, int j0)
{
    int j1;

    while (j0)
    {
        j1 = ctx->way[j0];
        ctx->p[j0] = ctx->p[j1];
        j0 = j1;
    }
}

double hungarian(double **cost, int a, int b, int *match_to)
{
    Hungarian_ctx ctx;
    int n, i, i0, j, j0, j1;
    double result, delta, cur;

    n = (a > b) ? a : b;
    if (!init_hungarian_ctx(&ctx, n))
        return (-1);
    result = 0.0;
    for (i = 1; i <= a; i++)
    {
        ctx.p[0] = i;
        init_row(&ctx);
        j0 = 0;
        ctx.way[j0] = 0;
        do {
            ctx.used[j0] = 1;
            i0 = ctx.p[j0];
            j1 = 0;
            for (j = 1; j <= b; j++)
            {
                if (!ctx.used[j])
                {
                    cur = cost[i0 - 1][j - 1] - ctx.u[i0] - ctx.v[j];
                    if (cur < ctx.minv[j])
                    {
                        ctx.minv[j] = cur;
                        ctx.way[j] = j0;
                    }
                }
            }
            find_min(&ctx, &delta, &j1);
            update_labels(&ctx, delta);
            j0 = j1;
        } while (ctx.p[j0] != 0);
        augment_path(&ctx, j0);
    }
    for (j = 1; j <= b; j++)
    {
        if (ctx.p[j] > 0 && ctx.p[j] <= a)
            match_to[j - 1] = ctx.p[j] - 1;
        else
            match_to[j - 1] = -1;
    }
    for (j = 1; j <= b; j++)
    {
        if (match_to[j - 1] != -1)
            result += cost[match_to[j - 1]][j - 1];
    }
    free_hungarian_ctx(&ctx);
    return result;
}
