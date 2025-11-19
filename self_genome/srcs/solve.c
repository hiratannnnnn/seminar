#include "genome.h"

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
	Adjacency **adj_A, Adjacency **adj_B, int log_output)
{
	int i, n, n_sent, nb_sent;
	int *perm_sent, *sigma_sent, *pb_sent, *sb_sent;
	Extremity *left, *right;
	int sign_diff;

	n = ctx->n;
	n_sent = ctx->n_sent;
	nb_sent = ctx->nb_sent;
	perm_sent = ctx->perm_sent;
	sigma_sent = ctx->sigma_sent;
	pb_sent = ctx->pb_sent;
	sb_sent = ctx->sb_sent;
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

static int track_paths(Extremity_ctx *ctx, Adjacency **adj_A, Adjacency **adj_B, int log_output)
{
	int i, n, n_sent, cycles, odd_paths;
	int len_l, len_r;
	Extremity *left, *right;
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
		left = cur->left;
		right = cur->right;
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

int solve_dcj_mine(Extremity_ctx *ctx, int log_output)
{
	int i,  n, n_sent, nb_sent;
	int cycles, odd_paths;
	int *perm_sent, *sigma_sent, *pb_sent, *sb_sent;
	Extremity *left, *right;
	Adjacency **adj_A, **adj_B;
	int sign_diff;

	n = ctx->n;
	n_sent = ctx->n_sent;
	nb_sent = ctx->nb_sent;
	perm_sent = ctx->perm_sent;
	sigma_sent = ctx->sigma_sent;
	pb_sent = ctx->pb_sent;
	sb_sent = ctx->sb_sent;
	cycles = 0;
	odd_paths = 0;

	int *map_A = (int *)xcalloc((2 * n), sizeof(int));
	int	*map_B = (int *)xcalloc((2 * n), sizeof(int));
	adj_A = (Adjacency **)xmalloc(sizeof(Adjacency *) * (n_sent - 1));
	adj_B = (Adjacency **)xmalloc(sizeof(Adjacency *) * (nb_sent - 1));
	set_maps_adjs(ctx, map_A, map_B, adj_A, adj_B, log_output);
	put_adjs(ctx, map_A, map_B, adj_A, adj_B, log_output);
	track_paths(ctx, adj_A, adj_B, log_output);
	free_array_int(map_A, 2 * n);
	free_array_int(map_B, 2 * n);
	free_list_adj(adj_A, n_sent - 1);
	free_list_adj(adj_B, nb_sent - 1);
	return (1);
}
