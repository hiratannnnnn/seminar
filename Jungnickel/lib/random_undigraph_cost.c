#include "lib.h"

double **gen_rand_undigraph_dbcost(int n, double max)
{
	double **matrix;
	int i, j;

	matrix = gen_matrix_double(n, n);
	if (!matrix)
		return NULL;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			matrix[i][j] = matrix[j][i] = (double)rand() / RAND_MAX * max;
	return matrix;
}

int **gen_rand_undigraph_intcost(int n, int max)
{
    int **matrix;
    int i, j;

    matrix = gen_matrix_int(n, n);
    if (!matrix)
        return NULL;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            matrix[i][j] = matrix[j][i] = rand() % max + 1;
    return matrix;
}
