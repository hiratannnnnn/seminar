#include "lib.h"

/**
 * @brief Creates an adjacency matrix with specified dimensions
 *
 * Dynamically allocates a 2D array of integers with r rows and c columns.
 * All elements are initialized to 0. This matrix can be used to represent
 * graph connections where a non-zero value at position [i][j] indicates
 * an edge between vertices i and j.
 *
 * @param r Number of rows (typically number of vertices)
 * @param c Number of columns (typically number of vertices)
 * @return Pointer to the allocated 2D array, or NULL if allocation fails
 */

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

int		**copy_matrix(int **matrix, int r, int c)
{
	int **dest;
	int i, j;

	dest = generate_matrix_int(r, c);
	if (!dest)
		return (NULL);
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
			dest[i][j] = matrix[i][j];
	return dest;
}

void	free_matrix_int(int **matrix, int const r, int const c)
{
	int i;

	i = 0;
	while (i < r)
	{
		xfree(matrix[i], sizeof(int) * c);
		i++;
	}
	xfree(matrix, sizeof(int *) * r);
}

void 	save_some_matrix(int n, double edge_prob,
	int **(*gen_some_mat)(int, double), char const *filename)
{
	int **matrix;

	matrix = gen_some_mat(n, edge_prob);
	if (!matrix)
		return ;
	write_adjacent_matrix(matrix, n, filename);
	free_matrix_int(matrix, n, n);
}
