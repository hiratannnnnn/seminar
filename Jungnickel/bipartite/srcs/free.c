#include "bipartite.h"

void	free_array_int(int *ptr, int const c)
{
	if (!ptr)
		return ;
	xfree(ptr, sizeof(int) * c);
}

void 	free_matrix_int(int **matrix, int const r, int const c)
{
	int i;

	for (i = 0; i < r; i++)
		free_array_int(matrix[i], c);
	xfree(matrix, sizeof(int *) * r);
}


void	free_array_double(double *ptr, int const c)
{
	if (!ptr)
		return ;
	xfree(ptr, sizeof(double) * c);
}

void	free_matrix_double(double **matrix, int const r, int const c)
{
	int i;

	for (i = 0; i < r; i++)
		xfree(matrix[i], sizeof(double) * c);
	xfree(matrix, sizeof(double *) * r);
}

void	free_array_char(char *ptr, int n)
{
	if (!ptr)
		return ;
	xfree(ptr, sizeof(char) * (n + 1));
}
