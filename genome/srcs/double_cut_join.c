#include "genome.h"

void dcj_parallel(Extremity_ctx *ctx, Adjacency *a, Adjacency *b)
{
	Extremity *a_left, *a_right, *b_left, *b_right;
	// Adjacency *a_left_to, *a_right_to, *b_left_to, *b_right_to;

	printf("%p\n", ctx);
	a_left = a->left;
	a_right = a->right;
	b_left = b->left;
	b_right = b->right;
	// a_left_to =a->left_to;
	// a_right_to = a->right_to;
	// b_left_to = b->left_to;
	// b_right_to = b->right_to;
	// cut a
	// cut b
	// join a_left & b_left
	// join a_right & b_right
	a_left->reality = b_right;
	a_right->reality = b_left;
	b_left->reality = a_right;
	b_right->reality = a_left;
	// a->left = b_left;
	// a->right = b_right;
	// b->left = a_left;
	// b->right = a_right;
	// a->left_to = b_left_to;
	// a->right_to = b_right_to;
	// b->left_to = a_left_to;
	// b->right_to = a_right_to;
}

void dcj_adverse(Extremity_ctx *ctx, Adjacency *a, Adjacency *b)
{
	Extremity *a_left, *a_right, *b_left, *b_right;
	// Adjacency *a_left_to, *a_right_to, *b_left_to, *b_right_to;

	printf("%p\n", ctx);
	a_left = a->left;
	a_right = a->right;
	b_left = b->left;
	b_right = b->right;
	// a_left_to =a->left_to;
	// a_right_to = a->right_to;
	// b_left_to = b->left_to;
	// b_right_to = b->right_to;
	// cut a
	// cut b
	// join a_left & b_right
	// join a_right & b_left
	a_left->reality = b_left;
	a_right->reality = b_right;
	b_right->reality = a_right;
	b_left->reality = a_left;
	// a->left = b_right;
	// a->right = b_left;
	// b->left = a_left;
	// b->right = a_right;
	// a->left_to = b_right_to;
	// a->right_to = b_left_to;
	// b->left_to = a_left_to;
	// b->right_to = a_right_to;
}

// void double_cut_join(Extremity_ctx *ctx, Extremity *a, Extremity)
void	double_cut_join2(Extremity_ctx *ctx, Adjacency *a, Adjacency *b, Cut_type type)
{
	Extremity *a_left, *a_right, *b_left, *b_right;

	a_left = a->left;
	a_right = a->right;
	b_left = b->left;
	b_right = b->right;
	printf("Cut_type: %d\n", type);
	if (!is_nullish(ctx, a_left) && !is_nullish(ctx, a_right))
	{
		if (!is_nullish(ctx, b_left) && !is_nullish(ctx, b_right))
		{
			printf("this is the case of (1, 2) and (3, 4)\n");
			if (type == PARALLEL)
				dcj_parallel(ctx, a, b);
			else
				dcj_adverse(ctx, a, b);
		}
		if (is_nullish(ctx, b_left) && !is_nullish(ctx, b_right))
		{
			printf("this is the case of (1, 2) and (o, 4)\n");
			if (type == PARALLEL)
				dcj_parallel(ctx, a, b);
			else
				dcj_adverse(ctx, a, b);
		}
		if (!is_nullish(ctx, b_left) && is_nullish(ctx, b_right))
		{
			printf("this is the case of (1, 2) and (3, o)\n");
			if (type == PARALLEL)
				dcj_parallel(ctx, a, b);
			else
				dcj_adverse(ctx, a, b);
		}
		if (is_nullish(ctx, b_left) && is_nullish(ctx, b_right))
		{
			printf("this is the case of (1, 2) and (o, o)\n");
			dcj_parallel(ctx, a, b);
		}
	}
	if (is_nullish(ctx, a_left) && !is_nullish(ctx, a_right))
	{
		if (!is_nullish(ctx, b_left) && !is_nullish(ctx, b_right))
		{
			printf("this is the case of (o, 2) and (3, 4)\n");
			if (type == PARALLEL)
				dcj_parallel(ctx, a, b);
			else
				dcj_adverse(ctx, a, b);
		}
		if (is_nullish(ctx, b_left) && !is_nullish(ctx, b_right))
		{
			printf("this is the case of (o, 2) and (o, 4)\n");
			dcj_adverse(ctx, a, b);
		}
		if (!is_nullish(ctx, b_left) && is_nullish(ctx, b_right))
		{
			printf("this is the case of (o, 2) and (3, o)\n");
			dcj_parallel(ctx, a, b);
		}
		if (is_nullish(ctx, b_left) && is_nullish(ctx, b_right))
		{
			printf("this is the case of (o, 2) and (o, o)\n");
			return ;
		}
	}
	if (!is_nullish(ctx, a_left) && is_nullish(ctx, a_right))
	{
		if (!is_nullish(ctx, b_left) && !is_nullish(ctx, b_right))
		{
			printf("this is the case of (1, o) and (3, 4)\n");
			if (type == PARALLEL)
				dcj_parallel(ctx, a, b);
			else
				dcj_adverse(ctx, a, b);
		}
		if (is_nullish(ctx, b_left) && !is_nullish(ctx, b_right))
		{
			printf("this is the case of (1, o) and (o, 4)\n");
			dcj_parallel(ctx, a, b);
		}
		if (!is_nullish(ctx, b_left) && is_nullish(ctx, b_right))
		{
			printf("this is the case of (1, o) and (3, o)\n");
			dcj_adverse(ctx, a, b);
		}
		if (is_nullish(ctx, b_left) && is_nullish(ctx, b_right))
		{
			printf("this is the case of (1, o) and (o, o)\n");
			return ;
		}
	}
	if (is_nullish(ctx, a_left) && is_nullish(ctx, a_right))
	{
		if (!is_nullish(ctx, b_left) && !is_nullish(ctx, b_right))
		{
			printf("this is the case of (o, o) and (3, 4)\n");
			dcj_parallel(ctx, a, b);

		}
		if (is_nullish(ctx, b_left) && !is_nullish(ctx, b_right))
		{
			printf("this is the case of (o, o) and (o, 4)\n");
			return ;
		}
		if (!is_nullish(ctx, b_left) && is_nullish(ctx, b_right))
		{
			printf("this is the case of (o, o) and (3, o)\n");
			return ;
		}
		if (is_nullish(ctx, b_left) && is_nullish(ctx, b_right))
		{
			printf("this is the case of (o, o) and (o, o)\n");
			return ;
		}
	}
}

void double_cut_join(Extremity_ctx *ctx, Extremity *src, Extremity *tar)
{
	Extremity *e1, *e2, *tmp1, *tmp2;

	if (is_nullish(ctx, tar))
	{
		if (src->sign == -1)
		{
			e1 = src;
			e2 = src->reality;
			e1->reality = ctx->ext_l;
			e2->reality = ctx->ext_r;
		}
		else
		{
			e1 = src;
			e2 = src->reality;
			e1->reality = ctx->ext_r;
			e2->reality = ctx->ext_l;
		}
		return ;
	}
	else
	{
		tmp1 = src->reality;
		src->reality = tar;
		tmp1->reality = tar->reality;
		tmp2 = tar->reality;
		tar->reality = src;
		tmp2->reality = tmp1;
	}
}
