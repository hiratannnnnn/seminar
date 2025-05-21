#include "lib.h"

/**
 * @brief Generates a random directed adjacency matrix and writes it to a file.
 *
 * @param n Number of vertices
 * @param edge_prob 0.0～1.0, edge probability between any two vertices
 */

int 	**generate_random_digraph(int n, double edge_prob)
{
	int **matrix;
	int i, j;

	// initialization
	matrix = generate_matrix(n, n);
	if (!matrix)
		return (NULL);
	// initialization

	srand((unsigned int)time(NULL));
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (i == j) continue;
			if ((double)rand() / RAND_MAX < edge_prob)
				matrix[i][j] = 1;
		}
	return (matrix);
}
