#include "mintree.h"
#include "path.h"

typedef struct Steiner_ctx
{
	double W;
	double **dist;
	EdgeNode *T;

}				Steiner_ctx;

static void steiner_free(Steiner_ctx *ctx, int n)
{
	if (ctx->dist)
		free_matrix_double(ctx->dist, n, n);
	if (ctx->T)
		free_edgenode(&ctx->T);
}

static int steiner_init(Steiner_ctx *ctx, double **cost, int n)
{
	ctx->dist = solve_floyd_d(cost, n);
	if (!ctx->dist)
		return (steiner_free(ctx, n), 0);
	
	ctx->W = DBL_MAX;
	ctx->T = NULL;
	return (1);
}

void solve_steiner(double **cost, int n)
{
	Steiner_ctx ctx;
	if (!steiner_init(&ctx, cost, n))
		return ;

	print_matrix_double(ctx.dist, n, n, 3);
	steiner_free(&ctx, n);
}
