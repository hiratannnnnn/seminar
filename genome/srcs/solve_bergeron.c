#include "genome.h"

// for algorithm on Bergeron (2009)

typedef struct TreeNode
{
	NodeType type;
	int start;
	int end;
	struct TreeNode **children;
	int n_children;
	struct TreeNode *parent;
}			TreeNode;

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

void add_child(TreeNode *parent, TreeNode *child)
{
	parent->children = (TreeNode **)realloc(parent->children, sizeof(TreeNode *) * (parent->n_children + 1));
	parent->children[parent->n_children] = child;
	parent->n_children++;
	child->parent = parent;
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

TreeNode *build_tree(Components *cmps, int n_sent)
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
	for (i = 0; i < n_sent; i++)
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

int solve_dcj(Extremity_ctx *ctx)
{
    Components cmps;
    int *maxes, *mins;
    int i, n;
    int n_sent;
    int leaf_count, long_branch_count, short_branch_count, dHP;
    TreeNode *T, *T0;

    n = ctx->n;
    n_sent = ctx->n_sent;
    printf("n:%d, n_sent:%d\n", n, n_sent);

    maxes = (int *)xmalloc(sizeof(int) * n_sent);
    mins  = (int *)xmalloc(sizeof(int) * n_sent);
    cmps.starts = (int *)xmalloc(sizeof(int) * n_sent);
    cmps.ends   = (int *)xmalloc(sizeof(int) * n_sent);
    if (!maxes || !mins || !cmps.starts || !cmps.ends)
        return -1;

    for (i = 0; i < n_sent; i++) {
        cmps.starts[i] = -1;
        cmps.ends[i]   = -1;
    }
    printf("allocated arrays.\n");
    preprocess(ctx, maxes, mins);
    print_array_int(maxes, n_sent, 3);
    print_array_int(mins, n_sent, 3);

    find_components_1(ctx, maxes, mins, &cmps);

	printf("starts ends\n");
    print_array_int(cmps.starts, n_sent, 3);
    print_array_int(cmps.ends, n_sent, 3);
	print_perm_sent(ctx->perm_sent, ctx->sigma_sent, ctx->n_sent);

    T  = build_tree(&cmps, n_sent);
    T0 = simplify_tree(T);

    leaf_count = long_branch_count = short_branch_count = 0;
    dfs_cover(T0, &leaf_count, &long_branch_count, &short_branch_count);

    printf("leaf_count: %d, long_branch_count: %d, short_branch_count: %d\n",
           leaf_count, long_branch_count, short_branch_count);

    int t = long_branch_count;
    dHP = leaf_count + short_branch_count + t;

    printf("Estimated DCJ distance (dHP): %d\n", dHP);

    free_tree(T0);
    free_array_int(maxes, n_sent);
    free_array_int(mins, n_sent);
    free_array_int(cmps.starts, n_sent);
    free_array_int(cmps.ends, n_sent);
    return dHP;
}
