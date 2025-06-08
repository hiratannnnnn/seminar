#include "bipartite.h"

double **generate_random_bigraph_cost(int a, int b)
{
	double **matrix;
	int i, j;

	matrix = generate_matrix_double(a, b);
	if (!matrix)
		return NULL;
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			matrix[i][j] = (double)rand() / RAND_MAX;
	return matrix;
}
