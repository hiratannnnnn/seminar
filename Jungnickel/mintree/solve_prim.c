#include "mintree.h"

// this is for the array g in the alg. 4.4.3.
typedef struct	PrimInfo
{
	double 	min_cost;
	Edge 	*edge;
}				PrimInfo;

typedef struct	Prim_ctx
{
	PrimInfo 	*cost_to_S;
	PathNode 	*S;
	EdgeNode 	*T;
	int 		one_based;
}				Prim_ctx;

static void	prim_free(Prim_ctx *ctx, int n)
{
	if (ctx->cost_to_S)
		xfree(ctx->cost_to_S, sizeof(PrimInfo) * n);
	if (ctx->S)
		free_pathnode(&ctx->S);
	if (ctx->T)
		free_edgenode(&ctx->T);
}

/**
 * @return 0 memory allocation error
 * @return 1 successful
 */
static int		prim_init(Prim_ctx *ctx, int s, int n, int one_based)
{
	if (one_based != 0 && one_based != 1)
		return (printf("one_based must be 0 or 1.\n"), 0);
	if (s < 0 || n - 1 < s)
		return (printf("s must be 0 <= s <= n-1.\n"), 0);
	ctx->cost_to_S = (PrimInfo *)xmalloc(sizeof(PrimInfo) * n);
	if (!ctx->cost_to_S)
		return (0);
	for (int i = 0; i < n; i++)								// Alg (2)
	{
		if (i == s)	// for arbitrary start vertex s
			ctx->cost_to_S[s].min_cost = 0.0;				// Alg (1-1)
		else
			ctx->cost_to_S[i].min_cost = DBL_MAX;
		ctx->cost_to_S[i].edge = NULL;
	}
	ctx->S = NULL;											// Alg (1-2)
	ctx->T = NULL;											// Alg (1-3)
	ctx->one_based = one_based;
	return (1);
}

void	solve_prim(Vertex **vs, int s, int n, int one_based)
{
	Prim_ctx ctx;
	PathNode *node;
	Edge *edge;
	Min_V min;

	if (!prim_init(&ctx, s, n, one_based))
		return ;
	while (count_pathnodes(ctx.S) < n)						// Alg (3)
	{
		min.min_cost = DBL_MAX;
		min.v = NULL;
		for (int i = 0; i < n; i++)							// Alg (4)
		{
			if ((ctx.S == NULL || s != vs[i]->label) &&
				ctx.cost_to_S[i].min_cost < min.min_cost)
			{
				min.min_cost = ctx.cost_to_S[i].min_cost;
				min.v = vs[i];
			}
		}
		if (ctx.cost_to_S[min.v->id].edge)
			printf("[DEBUG] chose %d -> %d%s\n",
				ctx.cost_to_S[min.v->id].edge->from + ctx.one_based,
				ctx.cost_to_S[min.v->id].edge->to + ctx.one_based,
				ctx.one_based ? " (1-based index)" : "");
		printf("[DEBUG] merge S and %d%s\n",
				min.v->id + ctx.one_based,
				ctx.one_based ? " (1-based index)" : "");
		node = create_pathnode(vs[min.v->id]);
		vs[min.v->id]->label = s;
		append_pathnode(&ctx.S, node);
		print_pathnode(ctx.S, ctx.one_based);
		if (node->v->id != s)								// Alg (5)
			append_edgenode(&ctx.T, create_edgenode(ctx.cost_to_S[min.v->id].edge));
		edge = min.v->incidence;
		while (edge)
		{													// Alg (6) (7)
			if (s != vs[edge->to]->label &&
				ctx.cost_to_S[edge->to].min_cost > edge->cost)
			{
				ctx.cost_to_S[edge->to].min_cost = edge->cost;
				ctx.cost_to_S[edge->to].edge = edge;
			}
			edge = edge->next;
		}
	}
	print_edgenode(ctx.T, ctx.one_based);
	prim_free(&ctx, n);
}
