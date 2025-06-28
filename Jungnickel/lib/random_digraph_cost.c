#include "lib.h"

double **generate_random_digraph_dbcost(int n, double max)
{
	double **matrix;
	int i, j;

	matrix = generate_matrix_double(n, n);
	if (!matrix)
		return NULL;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
        {
            if (i == j) 
                continue;
            matrix[i][j] = (double)rand() / RAND_MAX * max;
        }
   	return matrix;
}

int **generate_random_digraph_intcost(int n, int max)
{
    int **matrix;
    int i, j;

    matrix = generate_matrix_int(n, n);
    if (!matrix)
        return NULL;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            matrix[i][j] = rand() % (max + 1);  // 0からmaxまでの整数
        }
    return matrix;
}
