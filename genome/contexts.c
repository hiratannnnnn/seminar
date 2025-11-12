#include "genome.h"

void	put_desires(Extremity **exts, Extremity *ext_l, Extremity *ext_r, int n)
{
	int i, j;
	Extremity *cur, *tar;
	int cur_id, cur_sign;
	int tar_id, tar_sign;

	for (i = 0; i < n * 2 ; i++)
	{
		cur = exts[i];
		cur_id = cur->id;
		cur_sign = cur->sign;
		tar_id = abs(cur_id) + cur_sign;
		tar_sign = cur_sign * (-1);
		// printf("desire edge on %d to %d\n",
		// 	cur_id * cur_sign, tar_id * tar_sign);
		if (tar_id == 0)
		{
			ext_l->desire = cur;
			cur->desire = ext_l;
		}
		else if (tar_id == n + 1)
		{
			ext_r->desire = cur;
			cur->desire = ext_r;
		}
		for (j = 0; j < n * 2; j++)
		{
			if (exts[j]->id == tar_id &&
				exts[j]->sign == tar_sign)
			{
				tar = exts[j];
				tar->desire = cur;
			}
		}
	}
}

void	put_realities(Extremity **exts, Extremity *ext_l, Extremity *ext_r, int *perm, int n)
{
	int i;
	int id1, id2, sign1, sign2;
	Extremity *ext1_right, *ext2_left;

	for (i = 0; i < n - 1; i++)
	{
		id1 = abs(perm[i]);
		sign1 = id1 / perm[i]; // no zeros
		id2 = abs(perm[i + 1]);
		sign2 = id2 / perm[i + 1];
		ext1_right = (sign1 == 1) ?
			exts[2 * (id1 - 1) + 1] :
			exts[2 * (id1 - 1)];
		ext2_left = (sign2 == 1) ?
			exts[2 * (id2 - 1)] :
			exts[2 * (id2 - 1) + 1];
		ext1_right->reality = ext2_left;
		ext2_left->reality = ext1_right;
	}

	Extremity *ext_first, *ext_last;
	id1 = abs(perm[0]);
	sign1 = id1 / perm[0];
	id2 = abs(perm[n - 1]);
	sign2 = id2 / perm[n - 1];
	// ext_first = (sign1 == 1) ?
	// 	exts[2 * (id1 - 1)] :
	// 	exts[2 * (id1 - 1) + 1];
	ext_first = get_ext_by_value(exts, (-1) * perm[0]);
	// ext_last = (sign2 == 1) ?
	// 	exts[2 * (id2 - 1) + 1] :
	// 	exts[2 * (id2 - 1)];
	ext_last = get_ext_by_value(exts, perm[n - 1]);
	ext_first->reality = ext_l;
	ext_l->reality = ext_first;
	ext_last->reality = ext_r;
	ext_r->reality = ext_last;
}

Extremity **perm_to_exts(int *perm, int n)
{
	Extremity **exts;
	int i, g_id;

	exts = (Extremity **)xmalloc(sizeof(Extremity *) * (n * 2));
	if (!exts)
		return (NULL);
	i = 0;
	while (i < n)
	{
		g_id = abs(perm[i]);
		exts[2 * (g_id - 1)] = create_ext(g_id, -1);
		exts[2 * (g_id - 1) + 1] = create_ext(g_id, 1);
		if (!exts[2 * (g_id - 1)] || !exts[2 * (g_id - 1) + 1])
			return (free_array_exts(exts, n), NULL);
		i++;
	}
	return (exts);
}

static void	chase_exts_first(Extremity_ctx *ctx)
{
	Extremity *cur, *pair, *start;
	int oriented;

	oriented = 1;
	cur = ctx->ext_l->reality;
	start = cur;
	while (1)
	{
		pair = get_pair_of(ctx, cur);
		if (pair->reality &&
			pair->reality != ctx->ext_r &&
			cur->sign != pair->reality->sign)
			oriented = 0;
		cur = pair->reality;
		if (cur == NULL ||
			cur == ctx->ext_l ||
			cur == ctx->ext_r ||
			cur == start)
			break;
	}
	ctx->head->oriented = oriented;
	ctx->head->start = start;
}

void	Extremity_free(Extremity_ctx *ctx, int n)
{
	if (ctx->exts)
		free_array_exts(ctx->exts, n);
	if (ctx->ext_l)
		free_ext(ctx->ext_l);
	if (ctx->ext_r)
		free_ext(ctx->ext_r);
	if (ctx->goals)
		free_array_exts(ctx->goals, n);
	if (ctx->goal_l)
		free_ext(ctx->goal_l);
	if (ctx->goal_r)
		free_ext(ctx->goal_r);
	if (ctx->head)
		free_component_list(ctx->head);
}

int Extremity_init(Extremity_ctx *ctx, int *perm, int n)
{
	ctx->exts = perm_to_exts(perm, n);
	if (!ctx->exts)
		return (Extremity_free(ctx, n), -1);
	ctx->ext_l = create_ext(0, 1);
	if (!ctx->ext_l)
		return (Extremity_free(ctx, n), -1);
	ctx->ext_r = create_ext(n + 1, -1);
	if (!ctx->ext_r)
		return (Extremity_free(ctx, n), -1);
	put_realities(ctx->exts, ctx->ext_l, ctx->ext_r, perm, n);
	put_desires(ctx->exts, ctx->ext_l, ctx->ext_r, n);
	ctx->n = n;
	ctx->perm = perm;
	ctx->head = create_component();
	if (!ctx->head)
		return (Extremity_free(ctx, n), -1);
	chase_exts_first(ctx);
	return (1);
}

void	print_Extremity_ctx(Extremity_ctx *ctx)
{
	printf("==========\n\n");
	print_array_exts(ctx->exts, ctx->n);
	print_array_exts(ctx->goals, ctx->n);

	printf("%p, %p, %p, %p\n", ctx->ext_l, ctx->ext_r, ctx->goal_l, ctx->goal_r);
	printf("n: %d\n", ctx->n);
	printf("n_cent: %d\n", ctx->n_cent);
	print_array_int(ctx->perm, ctx->n, 3);
	print_array_int(ctx->perm_cent, ctx->n_cent, 3);
	print_array_int(ctx->sigma_cent, ctx->n_cent, 3);

	print_components(ctx->head);



	printf("\n==========\n");

}
