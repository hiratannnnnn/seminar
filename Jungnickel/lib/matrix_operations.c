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

int	**generate_matrix(int r, int c)
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

	dest = generate_matrix(r, c);
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

/**
 * @brief Writes an adjacency matrix to a text file.
 *
 * The file will contain the number of vertices n in the first line,
 * followed by n lines each containing n integers (0 or 1) separated by space.
 *
 * @param matrix	Pointer to the 2D adjacency matrix (n, n)
 * @param n			Number of vertices (matrix size)
 * @param filename	Output file name
 *
 * @return 0		on success
 * @return -1		if the file could not be opened
 * @return -2 		if matrix or matrix[i] is NULL
 *
 * @note
 * - The file is opened in "w" mode.
 * - Error handling and memory deallocation must be performed by the caller.
 */

int write_adjacent_matrix(int **matrix, int n, char const *filename)
{
	FILE 	*fp;
	int 	i, j;

	if (!matrix)
		return (-2);
	fp = fopen(filename, "w");
	if (!fp)
	{
		printf("Failed to open file.\n");
		return (-1);
	}
	fprintf(fp, "%d\n", n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			if (!matrix[i])
				return (fclose(fp), -2);
			fprintf(fp, "%d%c", matrix[i][j], (j == n - 1) ? '\n' : ' ');
		}
	fclose(fp);
	return (0);
}

/**
 * @brief write adjacent list to file
 *
 * @param matrix adjacency matrix size of (n, n)
 * @param n 	 size
 * @param filename name of file
 */

int write_adjacent_list(int **matrix, int n, char const *filename)
{
	FILE 	*fp;
	int 	i, j, first;

	if (!matrix)
		return (-2);
	fp = fopen(filename, "w");
	if (!fp)
	{
		printf("Failed to open file.\n");
		return (-1);
	}
	fprintf(fp, "%d\n", n);
	for (i = 0; i < n; i++)
	{
		first = 1;
		fprintf(fp, "%d:", i);
		for (j = 0; j < n; j++)
		{
			if (matrix[i][j])
			{
				if (first)
					first = 0;
				else
					fprintf(fp, " ");
				fprintf(fp, "%d", j);
			}
		}
		fprintf(fp, "%c", '\n');
	}
	fclose(fp);
	return (0);
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
