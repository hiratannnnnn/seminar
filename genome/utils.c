
#include "genome.h"

void	free_ext(Extremity *ext)
{
	xfree(ext, sizeof(Extremity));
}

void 	free_array_exts(Extremity **exts, int n)
{
	int i;

	i = 0;
	while (i < n * 2)
	{
		if (exts[i])
			free_ext(exts[i]);
		i++;
	}
	xfree(exts, sizeof(Extremity *) * (n * 2));
}

Extremity *create_ext(int id, int sign)
{
	Extremity *ext;

	ext = (Extremity *)xmalloc(sizeof(Extremity) * 1);
	if (!ext)
		return (NULL);
	ext->id = id;
	ext->sign = sign;
	ext->reality = NULL;
	ext->desire = NULL;
	return (ext);
}

int is_all_true(int *array, int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (array[i] == 0)
			return (0);
	return (1);
}

Extremity *get_pair_of(Extremity_ctx *ctx, Extremity *ext)
{
	int n;

	n = ctx->n;
	if (ext->id == 0 || ext->id == n + 1)
		return ext;
	if (ext->sign == 1)
		return (ctx->exts[2 * (ext->id - 1)]);
	else
		return (ctx->exts[2 * (ext->id - 1) + 1]);
}

Extremity *get_ext_by_perm_index(Extremity_ctx *ctx, Extremity **exts, int index)
{
	int *perm;
	int sign;
	int id;

	perm = ctx->perm;
	id = abs(perm[index]);
	sign = (perm[index] > 0) ? 1 : 0;
	return (exts[2 * (id - 1) + sign]);
}

Extremity *get_ext_by_value(Extremity_ctx *ctx, Extremity **exts, int value)
{
	int id;
	int sign;
	int n;

	n = ctx->n;
	id = abs(value);
	if (id == 0)
		return (ctx->ext_l);
	if (id == n + 1)
		return (ctx->ext_r);
	sign = (value > 0) ? 1 : 0;
	return (exts[2 * (id - 1) + sign]);
}

int 	is_nullish(Extremity_ctx *ctx, Extremity *ext)
{
	return (ext == NULL ||
			ext == ctx->ext_l ||
			ext == ctx->ext_r);
}

void	reverse_p(Extremity_ctx *ctx, int *perm, int *sigma)
{
	int i, n, n_cent;
	Extremity *ext;

	n = ctx->n;
	n_cent = ctx->n_cent;
	i = 0;
	while (i < n_cent)
	{
		ext = get_ext_by_value(ctx, ctx->exts, perm[i] * sigma[i]);
		if (ext->reality == ctx->ext_l)
			ext->reality = ctx->ext_r;
		else if (ext->reality == ctx->ext_r)
			ext->reality = ctx->ext_l;
		ext = get_pair_of(ctx, ext);
		if (ext->reality == ctx->ext_l)
			ext->reality = ctx->ext_r;
		else if (ext->reality == ctx->ext_r)
			ext->reality = ctx->ext_l;
		if (perm[i] == 0 || perm[i] == n + 1)
		{
			perm[i] = n + 1 - perm[i];
			sigma[i] = (-1) * sigma[i];
		}
		i++;
	}
}
