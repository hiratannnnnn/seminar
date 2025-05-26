#include "lib.h"

/**
 * @brief make adjacency matrix of LINE GRAPH of given matrix. (adj. list)
 *
 * @param vs Adjacency List
 * @param n
 * @param is_undir 1, dir 0
 */
int		**line_graph_from_adj_list(Vertex **vs, int n, int *size, int is_undir)
{
	Node **node_array;
	Node *head, *ni;
	Edge *ei, *ej;
	size_t len, i, j;
	int **matrix;

	head = edge_list_from_adj_list(vs, n, is_undir);
	len = count_nodes(head);	*size = len;
	matrix = generate_matrix(len, len);
	if (!matrix)
	{
		free_node_list(head);
		return (NULL);
	}

	node_array = xmalloc(sizeof(Node *) * len);
	ni = head;
	for (i = 0; i < len && ni; i++, ni = ni->next)
		node_array[i] = ni;
	for (i = 0; i < len; i++)
	{
		ei = node_array[i]->edge;
		for (j = 0; j < len; j++)
		{
			ej = node_array[j]->edge;
			if (is_undir)
			{
				if (ei->from == ej->from ||
					ei->from == ej->to ||
					ei->to == ej->from ||
					ei->to == ej->to)
					matrix[i][j] = matrix[j][i] = 1;
			}
			else
			{
				if (ei->to == ej->from)
					matrix[i][j] = 1;
			}
		}
	}
	xfree(node_array, sizeof(Node *) * len);
	free_node_list(head);
	return matrix;
}
