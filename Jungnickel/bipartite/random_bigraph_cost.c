#include "bipartite.h"

double **generate_matrix_double(int r, int c)
{
	int i;
	double **matrix;

	matrix = (double **)xmalloc(sizeof(double *) * r);
	if (!matrix)
		return NULL;
	for (i = 0; i < r; i++)
	{
		matrix[i] = (double *)xcalloc(c, sizeof(double));
		if (!matrix[i])
		{
			free_matrix_double(matrix, i, c);
			return NULL;
		}
	}
	return matrix;
}

void	free_matrix_double(double **matrix, int const r, int const c)
{
	int i;

	for (i = 0; i < r; i++)
	{
		xfree(matrix[i], sizeof(double) * c);
	}
	xfree(matrix, sizeof(double *) * r);
}

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

void	print_matrix_double(double **matrix, int r, int c)
{
	int i;

	for (i = 0; i < r; i++)
		print_array_double(matrix[i], c);
}

void 	print_array_double(double *arr, int c)
{
	int j;

	for (j = 0; j < c; j++)
		printf("%.6f%c", arr[j], j == c - 1 ? '\n' : ' ');
}
