#include "mintree.h"

int is_in_Vi(PathNode *node, int index)
{
	PathNode *cur;

	cur = node;
	while (cur)
	{
		// printf("[DEBUG] searching for %d\n", index);
		if (cur->v->id == index)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int is_in_Vi_label(PathNode *node, int index)
{
	PathNode *cur;

	cur = node;
	while (cur)
	{
		if (cur->v->label == index)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void free_pathnode_array(PathNode **ps, int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (ps[i])
			free_pathnode(&ps[i]);
	xfree(ps, sizeof(PathNode *) * n);
}

int is_spanning_tree(EdgeNode *list, int n)
{
	EdgeNode *cur;
	Edge *edge;
	int **matrix;
	int result, count;

	result = 0;
	count = 0;
	matrix = gen_matrix_int(n, n);
	if (!matrix)
	{
		printf("memory allocation error.\n");
		return (-1);
	}
	cur = list;
	while (cur)
	{
		count++;
		edge = cur->edge;
		if (edge->from >= n || edge->to >= n)
		{
			printf("size of the graph seems wrong. %d -> %d, n = %d\n",
					edge->from, edge->from, n);
			free_matrix_int(matrix, n, n);
			return (-1);
		}
		matrix[edge->from][edge->to] = matrix[edge->to][edge->from] = 1;
		cur = cur->next;
	}
	result = is_tree(matrix, n);
	free_matrix_int(matrix, n, n);
	return (result && count == n - 1);
}
