#include "bipartite.h"

int	**generate_matrix_int(int r, int c)
{
	int	**result;
	int	i;
	int	j;

	if (r < 1 || c < 1)
		return NULL;

	result = (int **)xmalloc(sizeof(int *) * r);
	if (!result)
		return (NULL);
	i = 0;
	while (i < r)
	{
		result[i] = (int *)xmalloc(sizeof(int) * c);
		if (!result[i])
		{
			free_matrix_int(result, i, c);
			return (NULL);
		}
		j = 0;
		while (j < c)
		{
			result[i][j] = 0;
			j++;
		}
		i++;
	}
	return (result);
}

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
