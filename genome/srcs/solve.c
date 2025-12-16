# include "genome.h"

static Adjacency *choose_l_r(Extremity_ctx *ctx, Adjacency *next, Adjacency *prev)
{
	int v_1, v_2, v_3, v_4;

	v_1 = get_value_ext(ctx, prev->left);
	v_2 = get_value_ext(ctx, prev->right);
	v_3 = get_value_ext(ctx, next->left);
	v_4 = get_value_ext(ctx, next->right);
	if (v_3 == 0 || v_4 == 0)
		return NULL;
	else if (v_1 == v_3)
		return next->right_to;
	else if (v_1 == v_4)
		return next->left_to;
	else if (v_2 == v_3)
		return next->right_to;
	else if (v_2 == v_4)
		return next->left_to;
	return (printf("ERROR.\n"), NULL);
}

static int set_maps_adjs(Extremity_ctx *ctx, int *map_A, int *map_B,
	Adjacency **adj_A, Adjacency **adj_B, int log_output)
{
	int i, n, n_sent, nb_sent;
	int *perm_sent, *sigma_sent, *pb_sent, *sb_sent;
	Extremity *left, *right;

	n = ctx->n;
	n_sent = ctx->n_sent;
	nb_sent = ctx->nb_sent;
	perm_sent = ctx->perm_sent;
	sigma_sent = ctx->sigma_sent;
	pb_sent = ctx->pb_sent;
	sb_sent = ctx->sb_sent;
	for (i = 0; i < n_sent - 1; i++)
	{
		left = get_ext_by_value(ctx, ctx->exts, perm_sent[i] * sigma_sent[i]);
		right = get_ext_by_value(ctx, ctx->exts, perm_sent[i + 1] * sigma_sent[i + 1] * (-1));
		adj_A[i] = create_adj_node(left, right);
		if (!is_nullish(ctx, left))
		{
			map_A[left->id - 1] = i;
			map_A[left->id - 1 + n] = left->sign;
		}
	}
	for (i = 0; i < nb_sent - 1; i++)
	{
		left = get_ext_by_value(ctx, ctx->goals, pb_sent[i] * sb_sent[i]);
		right = get_ext_by_value(ctx, ctx->goals, pb_sent[i + 1] * sb_sent[i + 1] * (-1));
		adj_B[i] = create_adj_node(left, right);
		if (!is_nullish(ctx, left))
		{
			map_B[left->id - 1] = i;
			map_B[left->id - 1 + n] = left->sign;
		}
	}
	if (log_output)
	{
		printf("map_A: ");
		print_array_int(map_A, 2 * n, 2);
		printf("map_B: ");
		print_array_int(map_B, 2 * n, 2);
	}
	return (1);
}

static int put_adjs(Extremity_ctx *ctx, int *map_A, int *map_B,
	Adjacency **adj_A, Adjacency **adj_B)
{
	int i, n, n_sent, nb_sent;
	Extremity *left, *right;
	int sign_diff;

	n = ctx->n;
	n_sent = ctx->n_sent;
	nb_sent = ctx->nb_sent;
	for (i = 0; i < n_sent - 1; i++)
	{
		left = adj_A[i]->left;
		right = adj_A[i]->right;
		if (!is_nullish(ctx, left))
		{
			sign_diff = (left->sign == map_B[left->id - 1 + n]) ? 0 : 1;
			adj_A[i]->left_to = (sign_diff) ?
				adj_B[map_B[left->id - 1] - 1] :
				adj_B[map_B[left->id - 1]];
		}
		if (!is_nullish(ctx, right))
		{
			sign_diff = (right->sign == map_B[right->id - 1 + n]) ? 0 : 1;
			adj_A[i]->right_to = (sign_diff) ?
				adj_B[map_B[right->id - 1] - 1] :
				adj_B[map_B[right->id - 1]];
		}
	}
	for (i = 0; i < nb_sent - 1; i++)
	{
		left = adj_B[i]->left;
		right = adj_B[i]->right;
		if (!is_nullish(ctx, left))
		{
			sign_diff = (left->sign == map_A[left->id - 1 + n]) ? 0 : 1;
			adj_B[i]->left_to = (sign_diff) ?
				adj_A[map_A[left->id - 1] - 1] :
				adj_A[map_A[left->id - 1]];

		}
		if (!is_nullish(ctx, right))
		{
			sign_diff = (right->sign == map_A[right->id - 1 + n]) ? 0 : 1;
			adj_B[i]->right_to = (sign_diff) ?
				adj_A[map_A[right->id - 1] - 1] :
				adj_A[map_A[right->id - 1]];
		}
	}
	return (1);
}

static int track_paths(Extremity_ctx *ctx, Adjacency **adj_A, int log_output)
{
	int i, n, n_sent, cycles, odd_paths;
	int len_l, len_r;
	Adjacency *cur, *prev, *next, *seek_l, *seek_r, *last;

	n = ctx->n;
	n_sent = ctx->n_sent;
	cycles = odd_paths = 0;
	for (i = 0; i < n_sent - 1; i++)
	{
		if (adj_A[i]->visited)
		{
			if (log_output)
				printf("%d: visited.\n", i);
			continue;
		}
		cur = adj_A[i];
		if (log_output)
			printf("%d: STARTING FROM (%d, %d)\n", i,
				get_value_ext(ctx, cur->left),
				get_value_ext(ctx, cur->right));
		len_l = len_r = 0;
		seek_l = cur->left_to;
		seek_r = cur->right_to;
		last = NULL;
		cur->visited = 1;
		prev = cur;
		next = seek_l;
		while (next)
		{
			len_l++;
			if (log_output)
				printf("len: %d, seeking left. (%d, %d)\n", len_l,
					get_value_ext(ctx, next->left),
					get_value_ext(ctx, next->right));
			next->visited = 1;
			last = next;
			next = choose_l_r(ctx, next, prev);
			prev = last;
			if (cur == prev)
			{
				if (seek_r)
				{
					if (log_output)
						printf("found a cycle.\n");
					cycles++;
				}
				break;
			}
		}
		if (cur == last)
			continue;
		prev = cur;
		next = seek_r;
		while (next)
		{
			len_r++;
			if (log_output)
				printf("len: %d, seeking right. (%d, %d)\n", len_r,
					get_value_ext(ctx, next->left),
					get_value_ext(ctx, next->right));
			next->visited = 1;
			last = next;
			next = choose_l_r(ctx, next, prev);
			prev = last;
			if (cur == last)
			{
				// this must not happen.
				printf("ERROR.\n");
				break;
			}
		}
		if ((len_l + len_r) % 2 == 1)
		{
			if (log_output)
				printf("found an odd path.\n");
			odd_paths++;
		}
	}
	printf("N: %d, C: %d, I: %d\n", n, cycles, odd_paths);
	printf("d: %.1f\n", n - cycles - (odd_paths / 2.0));
	return (1);
}

static int is_diff(Extremity_ctx *ctx, Extremity *a, Extremity *b)
{
	if (!is_nullish(ctx,a))
	{
		if (a != b)
			return (1);
		else
			return (0);
	}
	else
	{
		if (a == b)
			return (0);
		if (is_nullish(ctx, b))
			return (0);
	}
	return (1);
}

static void proceed(Extremity_ctx *ctx, int log_output)
{
	Extremity **exts;
	Extremity **goals;
	Extremity *src;
	Extremity *tar;
	int tar_id;
	int tar_sign;
	int c;
	int i;

	exts = ctx->exts;
	goals = ctx->goals;
	c = 0;
	for (i = 0; i < (ctx->n) * 2; i++)
	{
		src = exts[i];
		tar_id = goals[i]->reality->id;
		tar_sign = goals[i]->reality->sign;
		tar_sign = (tar_sign == 1) ? 1 : 0;
		if (tar_id == 0)
			tar = ctx->ext_l;
		else if (tar_id == ctx->n + 1)
			tar = ctx->ext_r;
		else
			tar = exts[(tar_id - 1) * 2 + tar_sign];
		if (!is_nullish(ctx, tar) && is_diff(ctx, src->reality, tar))
		{
			if (log_output)
			{
				int src_num = src->id * src->sign;
				int tar_num = tar->id * tar->sign;
				int src_pair_num = src->reality->id * src->reality->sign;
				int tar_pair_num = tar->reality->id * tar->reality->sign;
				fprintf(ctx->fp, "(%d, %d) (%d, %d) --DCJ--> (%d, %d) (%d, %d)\n",
					src_num, src_pair_num, tar_num, tar_pair_num,
					src_num, tar_num, src_pair_num, tar_pair_num);
			}
			double_cut_join(ctx, src, tar);
			c++;
		}
	}
	for (i = 0; i < (ctx->n) * 2; i++)
	{
		src = exts[i];
		tar_id = goals[i]->reality->id;
		tar_sign = goals[i]->reality->sign;
		tar_sign = (tar_sign == 1) ? 1 : 0;
		if (tar_id == 0)
			tar = ctx->ext_l;
		else if (tar_id == ctx->n + 1)
			tar = ctx->ext_r;
		else
			tar = exts[(tar_id - 1) * 2 + tar_sign];
		if (is_nullish(ctx, tar) && is_diff(ctx, src->reality, tar))
		{
			if (log_output)
			{
				int src_num = src->id * src->sign;
				int tar_num = tar->id * tar->sign;
				int src_pair_num = src->reality->id * src->reality->sign;
				int tar_pair_num = tar->reality->id * tar->reality->sign;
				fprintf(ctx->fp, "(%d, %d) (%d, %d) --DCJ--> (%d, %d) (%d, %d)\n",
					src_num, src_pair_num, tar_num, tar_pair_num,
					src_num, tar_num, src_pair_num, tar_pair_num);
			}
			double_cut_join(ctx, src, tar);
			c++;
		}
	}
	if (log_output)
		fprintf(ctx->fp, "number of dcjs: %d\n", c);
}

int solve_dcj_mine(Extremity_ctx *ctx, int log_output)
{
	int *map_A, *map_B;
	Adjacency **adj_A, **adj_B;

	if (log_output)
	{
		ctx->fp = fopen("log", "w");
		if (!ctx->fp)
			return (-1);
	}
	map_A = (int *)xcalloc((2 * ctx->n), sizeof(int));
	map_B = (int *)xcalloc((2 * ctx->n), sizeof(int));
	adj_A = (Adjacency **)xmalloc(sizeof(Adjacency *) * (ctx->n_sent - 1));
	adj_B = (Adjacency **)xmalloc(sizeof(Adjacency *) * (ctx->nb_sent - 1));
	set_maps_adjs(ctx, map_A, map_B, adj_A, adj_B, log_output);
	put_adjs(ctx, map_A, map_B, adj_A, adj_B);
	track_paths(ctx, adj_A, log_output);
	proceed(ctx, log_output);
	free_array_int(map_A, 2 * ctx->n);
	free_array_int(map_B, 2 * ctx->n);
	free_list_adj(adj_A, ctx->n_sent - 1);
	free_list_adj(adj_B, ctx->nb_sent - 1);
	if (log_output)
		fclose(ctx->fp);
	return (1);
}
