#include "mintree.h"

typedef struct	PrimInfo
{
	double 	min_cost;
	Edge 	*edge;
}				PrimInfo;

typedef struct	Prim_ctx
{
	PrimInfo *cost_to_S;
	PathNode *S;
	EdgeNode *T;
}				Prim_ctx;

void	prim_free(Prim_ctx *ctx, int n)
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
int		prim_init(Prim_ctx *ctx, int s, int n)
{
	ctx->cost_to_S = (PrimInfo *)xmalloc(sizeof(PrimInfo) * n);
	if (!ctx->cost_to_S)
		return (0);
	for (int i = 0; i < n; i++)
	{
		if (i == s)
			ctx->cost_to_S[s].min_cost = 0.0;
		else
			ctx->cost_to_S[i].min_cost = DBL_MAX;
		ctx->cost_to_S[i].edge = NULL;
	}
	ctx->S = NULL;
	ctx->T = NULL;
	return (1);
}

void	solve_prim(Vertex **vs, int s, int n)
{
	Prim_ctx ctx;
	PathNode *node;
	Edge *edge;
	Min_V min;

	if (!prim_init(&ctx, s, n))
		return ;
	while (count_pathnodes(ctx.S) < n)
	{
		min.min_cost = DBL_MAX;
		min.v = NULL;
		for (int i = 0; i < n; i++)
		{
			if (!is_in_Vi(ctx.S, i) && ctx.cost_to_S[i].min_cost < min.min_cost)
			{
				min.min_cost = ctx.cost_to_S[i].min_cost;
				min.v = vs[i];
			}
		}
		printf("[DEBUG] merge S and %d\n", min.v->id);
		node = create_pathnode(vs[min.v->id]);
		append_pathnode(&ctx.S, node);
		print_pathnode(ctx.S);
		if (node->v->id != 0)
			append_edgenode(&ctx.T, create_edgenode(ctx.cost_to_S[min.v->id].edge));
		edge = min.v->incidence;
		while (edge)
		{
			if (!is_in_Vi(ctx.S, edge->to) && ctx.cost_to_S[edge->to].min_cost > edge->cost)
			{
				ctx.cost_to_S[edge->to].min_cost = edge->cost;
				ctx.cost_to_S[edge->to].edge = edge;
			}
			edge = edge->next;
		}
	}
	print_edgenode(ctx.T);
	prim_free(&ctx, n);
}
