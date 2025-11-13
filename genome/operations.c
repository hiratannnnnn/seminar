#include "genome.h"

void	cut_exts(Extremity_ctx *ctx, Extremity *left, Extremity *right)
{
	if (left->reality != right || right->reality != left)
	{
		printf("Cannot cut disconnected ones.\n");
		return ;
	}
	left->reality = ctx->ext_r;
	right->reality = ctx->ext_l;
}

void	join_exts(Extremity_ctx *ctx, Extremity *left, Extremity *right)
{
	if (!is_nullish(ctx, left->reality) || !is_nullish(ctx, right->reality))
	{
		printf("Cut the edge first.\n");
		return ;
	}
	left->reality = right;
	right->reality = left;
}
