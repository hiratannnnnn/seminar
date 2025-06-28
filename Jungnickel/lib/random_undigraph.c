#include "lib.h"

/**
 * @brief Generates a random undirected adjacency matrix and writes it to a file.
 *
 * @param n Number of vertices
 * @param edge_prob 0.0～1.0, edge probability between any two vertices
 */

int 	**generate_random_undigraph(int n, double edge_prob)
{
	int **matrix;
	int i, j;

	matrix = generate_matrix_int(n, n);
	if (!matrix)
		return (NULL);
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if ((double)rand() / RAND_MAX < edge_prob)
			{
				matrix[i][j] = 1;
				matrix[j][i] = 1; 
			}
		}
	}
	return (matrix);
}
