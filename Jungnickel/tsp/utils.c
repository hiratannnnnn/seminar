#include "tsp.h"

int **gen_weighted_matrix(int n, int upper)
{
	int **matrix;
	int i, j;

	matrix = gen_matrix_int(n, n);
	if (!matrix)
		return NULL;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			matrix[i][j] = matrix[j][i] = (rand() % upper) + 1;
	return matrix;
}
