#include "genome.h"

static void	put_desires(Extremity_ctx *ctx, int n)
{
	int i, j;
	Extremity *cur, *tar;
	int cur_id, cur_sign;
	int tar_id, tar_sign;

	for (i = 0; i < n * 2 ; i++)
	{
		cur = ctx->exts[i];
		cur_id = cur->id;
		cur_sign = cur->sign;
		tar_id = abs(cur_id) + cur_sign;
		tar_sign = cur_sign * (-1);
		printf("desire edge on %d to %d\n",
			cur_id * cur_sign, tar_id * tar_sign);
		if (tar_id == 0)
		{
			ctx->ext_l->desire = cur;
			cur->desire = ctx->ext_l;
		}
		else if (tar_id == n + 1)
		{
			ctx->ext_r->desire = cur;
			cur->desire = ctx->ext_r;
		}
		for (j = 0; j < n * 2; j++)
		{
			if (ctx->exts[j]->id == tar_id &&
				ctx->exts[j]->sign == tar_sign)
			{
				tar = ctx->exts[j];
				tar->desire = cur;
			}
		}
	}
}

static void	put_realities(Extremity_ctx *ctx, int *perm, int n)
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
			ctx->exts[2 * (id1 - 1) + 1] :
			ctx->exts[2 * (id1 - 1)];
		ext2_left = (sign2 == 1) ?
			ctx->exts[2 * (id2 - 1)] :
			ctx->exts[2 * (id2 - 1) + 1];
		ext1_right->reality = ext2_left;
		ext2_left->reality = ext1_right;
	}

	Extremity *ext_first, *ext_last;
	id1 = abs(perm[0]);
	sign1 = id1 / perm[0];
	id2 = abs(perm[n - 1]);
	sign2 = id2 / perm[n - 1];
	ext_first = (sign1 == 1) ?
		ctx->exts[2 * (id1 - 1)] :
		ctx->exts[2 * (id1 - 1) + 1];
	ext_last = (sign2 == 1) ?
		ctx->exts[2 * (id2 - 1) + 1] :
		ctx->exts[2 * (id2 - 1)];
	ext_first->reality = ctx->ext_l;
	ctx->ext_l->reality = ext_first;
	ext_last->reality = ctx->ext_r;
	ctx->ext_r->reality = ext_last;
}

static Extremity **perm_to_exts(int *perm, int n)
{
	Extremity **exts;
	int i, g_id;

	exts = (Extremity **)xmalloc(sizeof(Extremity *) * (n * 2));
	if (!exts)
		return (NULL);
	printf("sizeof(Extremity): %d\n", sizeof(Extremity));
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
	put_realities(ctx, perm, n);
	put_desires(ctx, n);
	ctx->n = n;
	ctx->perm = perm;
	ctx->head = create_component();
	if (!ctx->head)
		return (Extremity_free(ctx, n), -1);
	chase_exts_first(ctx);
	return (1);
}
