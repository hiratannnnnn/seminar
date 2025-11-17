# include "genome.h"

typedef struct TreeNode
{
	NodeType type;
	int start;
	int end;
	struct TreeNode **children;
	int n_children;
	struct TreeNode *parent;
}			TreeNode;

void add_child(TreeNode *parent, TreeNode *child)
{
	parent->children = (TreeNode **)realloc(parent->children, sizeof(TreeNode *) * (parent->n_children + 1));
	parent->children[parent->n_children] = child;
	parent->n_children++;
	child->parent = parent;
}

void free_tree(TreeNode *node)
{
	int i;

	if (!node)
		return ;
	for (i = 0; i < node->n_children; i++)
		free_tree(node->children[i]);
	xfree(node->children, sizeof(TreeNode *) * node->n_children);
	xfree(node, sizeof(TreeNode));
}

TreeNode *simplify_tree(TreeNode *node)
{
	int i;

	if (!node)
		return NULL;
	for (i = 0; i < node->n_children; i++)
		node->children[i] = simplify_tree(node->children[i]);
	if ((node->type == ROUND || node->type == SQUARE) && node->n_children == 0)
	{
		free(node->children);
		free(node);
		return (NULL);
	}
	return (node);
}

void	dfs_cover(TreeNode *node, int *leaf_c, int *long_b_c, int *short_b_c)
{
	int i;

	if (!node)
		return ;
	if (node->n_children == 0)
	{
		(*leaf_c)++;
		return ;
	}
	for (i = 0; i < node->n_children; i++)
		dfs_cover(node->children[i], leaf_c, long_b_c, short_b_c);
	if (node->n_children >= 2)
		(*long_b_c)++;
	else if (node->n_children == 1)
		(*short_b_c)++;
}

TreeNode *build_tree(Components *cmps, int n_cent)
{
	TreeNode *root, *p, *q, *new_q, *new_p;
	int i;

	root = (TreeNode *)xcalloc(1, sizeof(TreeNode));
	root->type = ROUND;
	root->children = NULL;
	root->n_children = 0;
	root->parent = NULL;
	p = root;
	q = NULL;
	for (i = 0; i < n_cent; i++)
	{
		if (cmps->starts[i] != -1)
		{
			if (cmps->ends[i] == -1)
			{
				new_q = (TreeNode *)xcalloc(1, sizeof(TreeNode));
				new_q->type = SQUARE;
				new_q->children = NULL;
				new_q->n_children = 0;
				add_child(p, new_q);
				q = new_q;
			}
			new_p = (TreeNode *)xcalloc(1, sizeof(TreeNode));
			new_p->type = ROUND;
			new_p->start = i;
			new_p->end = cmps->ends[i];
			new_p->children = NULL;
			new_p->n_children = 0;
			if (q)
				add_child(q, new_p);
			else
				add_child(p, new_p);
			p = new_p;
		}
		else if (cmps->ends[i] != -1)
		{
			if (p->parent)
				p = p->parent;
			if (q && q->parent)
				q = q->parent;
		}
	}
	return (root);
}

// int solve_dcj(Extremity_ctx *ctx)
// {
// 	Components cmps;
// 	int *maxes, *mins;
// 	int i, n;
// 	int n_cent;

// 	n = ctx->n;
// 	n_cent = ctx->n_cent;
// 	printf("n:%d, n_cent:%d\n", n, n_cent);
// 	// if (Extremity_init(ctx, perm, n) == -1)
// 	// 	return (-1);
// 	maxes = (int *)xmalloc(sizeof(int) * (n_cent));
// 	mins = (int *)xmalloc(sizeof(int) * (n_cent));
// 	cmps.starts = (int *)xmalloc(sizeof(int) * (n_cent));
// 	cmps.ends = (int *)xmalloc(sizeof(int) * (n_cent));
// 	if (!maxes || !mins || !cmps.starts || !cmps.ends)
// 		return (-1);
// 	for (i = 0; i < n_cent; i++)
// 	{
// 		cmps.starts[i] = -1;
// 		cmps.ends[i] = -1;
// 	}

// 	printf("allocated arrays.\n");
// 	preprocess(ctx, maxes, mins);
// 	print_array_int(maxes, n_cent, 3);
// 	print_array_int(mins, n_cent, 3);

// 	// print_array_exts(ctx->exts, n);
// 	print_chromosomes(ctx, n);
// 	print_components(ctx->head);
// 	find_components_1(ctx, maxes, mins, &cmps);

// 	print_array_int(ctx->sigma_cent, n_cent, 3);
// 	print_array_int(ctx->perm_cent, n_cent, 3);
// 	print_array_int(cmps.ends, n_cent, 3);
// 	print_array_int(cmps.starts, n_cent, 3);
// 	// free
// 	free_array_int(maxes, n_cent);
// 	free_array_int(mins, n_cent);
// 	free_array_int(cmps.starts, n_cent);
// 	free_array_int(cmps.ends, n_cent);
// 	return (1);
// }

Adjacency *create_adj_node(Extremity *left, Extremity *right)
{
	Adjacency *tmp;

	tmp = (Adjacency *)xmalloc(sizeof(Adjacency) * 1);
	tmp->left = left;
	tmp->right = right;
	tmp->left_to = NULL;
	tmp->right_to = NULL;
	tmp->visited = 0;
	return (tmp);
}

int get_value_ext(Extremity_ctx *ctx, Extremity *ext)
{
	if (is_nullish(ctx, ext))
		return (0);
	return (ext->id * ext->sign);
}

Adjacency *choose_l_r(Extremity_ctx *ctx, Adjacency *next, Adjacency *prev)
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

void	free_list_adj(Adjacency **list, int n)
{
	int i;

	i = 0;
	while (i < n)
		xfree(list[i++], sizeof(Adjacency));
	xfree(list, sizeof(Adjacency *) * n);
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
	// for (i = 0; i < n_cent - 1; i++)
	// {
	// 	left = adj_A[i]->left;
	// 	right = adj_A[i]->right;
	// 	printf("%d, %p\n", (is_nullish(ctx, left)) ?
	// 		-1 : adj_A[i]->left_to->left->id *
	// 			 adj_A[i]->left_to->left->sign, adj_A[i]->right_to);
	// }
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
	// nl(1);
	// for (i = 0; i < nb_cent - 1; i++)
	// {
	// 	printf("%p, %p\n", adj_B[i]->left_to, adj_B[i]->right_to);
	// }
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
			// if (get_value_ext(ctx, next->left) == get_value_ext(ctx, prev->left))
			// 	next = next->right_to;
			// else
			// 	next = next->left_to;
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
			// if (get_value_ext(ctx, next->right) == get_value_ext(ctx, prev->right))
			// 	next = next->right_to;
			// else
			// 	next = next->left_to;
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


int solve_dcj(Extremity_ctx *ctx)
{
    Components cmps;
    int *maxes, *mins;
    int i, n;
    int n_cent;
    int leaf_count, long_branch_count, short_branch_count, dHP;
    TreeNode *T, *T0;

    n = ctx->n;
    n_cent = ctx->n_cent;
    printf("n:%d, n_cent:%d\n", n, n_cent);

    maxes = (int *)xmalloc(sizeof(int) * n_cent);
    mins  = (int *)xmalloc(sizeof(int) * n_cent);
    cmps.starts = (int *)xmalloc(sizeof(int) * n_cent);
    cmps.ends   = (int *)xmalloc(sizeof(int) * n_cent);
    if (!maxes || !mins || !cmps.starts || !cmps.ends)
        return -1;

    for (i = 0; i < n_cent; i++) {
        cmps.starts[i] = -1;
        cmps.ends[i]   = -1;
    }
    printf("allocated arrays.\n");
    preprocess(ctx, maxes, mins);
    print_array_int(maxes, n_cent, 3);
    print_array_int(mins, n_cent, 3);

    find_components_1(ctx, maxes, mins, &cmps);

	printf("starts ends\n");
    print_array_int(cmps.starts, n_cent, 3);
    print_array_int(cmps.ends, n_cent, 3);
	print_components(ctx, &cmps);
	print_perm_cent(ctx->perm_cent, ctx->sigma_cent, ctx->n_cent);

    T  = build_tree(&cmps, n_cent);
    T0 = simplify_tree(T);

    leaf_count = long_branch_count = short_branch_count = 0;
    dfs_cover(T0, &leaf_count, &long_branch_count, &short_branch_count);

    printf("leaf_count: %d, long_branch_count: %d, short_branch_count: %d\n",
           leaf_count, long_branch_count, short_branch_count);

    int t = long_branch_count;
    dHP = leaf_count + short_branch_count + t;

    printf("Estimated DCJ distance (dHP): %d\n", dHP);

    free_tree(T0);
    free_array_int(maxes, n_cent);
    free_array_int(mins, n_cent);
    free_array_int(cmps.starts, n_cent);
    free_array_int(cmps.ends, n_cent);
    return dHP;
}
