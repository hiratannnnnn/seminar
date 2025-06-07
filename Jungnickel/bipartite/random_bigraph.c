#include "bipartite.h"

int **generate_random_bigraph(int a, int b, double edge_prob)
{
	int **matrix;
	int i, j;

	matrix = generate_matrix(a, b);
	if (!matrix)
		return NULL;
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			if ((double) rand() / RAND_MAX <= edge_prob)
				matrix[i][j] = matrix[j][i] = 1;
	return matrix;
}
