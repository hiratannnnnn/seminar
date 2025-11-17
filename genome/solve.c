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

int solve_dcj_mine(Extremity_ctx *ctx)
{
	int i,  n, n_cent, nb_cent;
	int cycles, odd_paths;
	int *perm_cent, *sigma_cent, *pb_cent, *sb_cent;
	Extremity *left, *right;
	Adjacency **adj_A, **adj_B;
	int sign_diff;

	n = ctx->n;
	n_cent = ctx->n_cent;
	nb_cent = ctx->nb_cent;
	perm_cent = ctx->perm_cent;
	sigma_cent = ctx->sigma_cent;
	pb_cent = ctx->pb_cent;
	sb_cent = ctx->sb_cent;
	cycles = 0;
	odd_paths = 0;
	printf("%d, %d\n", cycles, odd_paths);

	int *map_A = (int *)xcalloc((2 * n), sizeof(int));
	int	*map_B = (int *)xcalloc((2 * n), sizeof(int));
	adj_A = (Adjacency **)xmalloc(sizeof(Adjacency *) * (n_cent - 1));
	adj_B = (Adjacency **)xmalloc(sizeof(Adjacency *) * (nb_cent - 1));
	for (i = 0; i < n_cent - 1; i++)
	{
		left = get_ext_by_value(ctx, ctx->exts, perm_cent[i] * sigma_cent[i]);
		right = get_ext_by_value(ctx, ctx->exts, perm_cent[i + 1] * sigma_cent[i + 1] * (-1));
		adj_A[i] = create_adj_node(left, right);
		if (!is_nullish(ctx, left))
		{
			map_A[left->id - 1] = i;
			map_A[left->id - 1 + n] = left->sign;
		}
	}
	for (i = 0; i < nb_cent - 1; i++)
	{
		left = get_ext_by_value(ctx, ctx->goals, pb_cent[i] * sb_cent[i]);
		right = get_ext_by_value(ctx, ctx->goals, pb_cent[i + 1] * sb_cent[i + 1] * (-1));
		adj_B[i] = create_adj_node(left, right);
		if (!is_nullish(ctx, left))
		{
			map_B[left->id - 1] = i;
			map_B[left->id - 1 + n] = left->sign;
		}
	}
	print_array_int(map_A, 2 * n, 2);
	print_array_int(map_B, 2 * n, 2);
	for (i = 0; i < n_cent - 1; i++)
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
	for (i = 0; i < nb_cent - 1; i++)
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
	int len_l, len_r;
	Adjacency *cur, *next, *prev, *seek_l, *seek_r, *last_l, *last_r;

	for (i = 0; i < n_cent - 1; i++)
	{
		if (adj_A[i]->visited)
		{
			printf("%d: visited.\n", i);
			continue;
		}
		cur = adj_A[i];
		printf("%d: STARTING FROM (%d, %d)\n", i, get_value_ext(ctx, cur->left), get_value_ext(ctx, cur->right));
		len_l = 0;
		len_r = 0;
		left = cur->left;
		right = cur->right;
		seek_l = cur->left_to;
		seek_r = cur->right_to;
		last_l = NULL;
		cur->visited = 1;

		prev = cur;
		next = seek_l;
		while (next)
		{
			len_l++;
			printf("len: %d, seeking left.(%d, %d)\n", len_l, get_value_ext(ctx, next->left), get_value_ext(ctx, next->right));
			next->visited = 1;
			last_l = next;
			next = choose_l_r(ctx, next, prev);
			prev = last_l;
			if (cur == prev)
			{
				if (seek_r)
				{
					printf("found a cycle.\n");
					cycles++;
				}
				break;
			}
		}
		if (cur == last_l)
			continue;
		prev = cur;
		next = seek_r;
		while (next)
		{
			len_r++;
			printf("len: %d, seeking right.(%d, %d)\n", len_r, get_value_ext(ctx, next->left), get_value_ext(ctx, next->right));
			next->visited = 1;
			last_r = next;
			next = choose_l_r(ctx, next, prev);
			prev = last_r;
			if (cur == last_r)
			{
				printf("error?\n");
				break;
			}
		}
		if ((len_l + len_r) % 2 == 1)
		{
			printf("found an odd path.\n");
			odd_paths++;
		}
	}
	printf("N: %d, C: %d, I: %d\n", n, cycles, odd_paths);
	printf("d: %f\n", n - cycles - (odd_paths / 2.0));
	free_array_int(map_A, 2 * n);
	free_array_int(map_B, 2 * n);
	free_list_adj(adj_A, n_cent - 1);
	free_list_adj(adj_B, nb_cent - 1);
	return (1);
}
