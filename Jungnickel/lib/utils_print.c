#include "../jung.h"

void print_matrix(int **matrix, int r, int c)
{
	if (!matrix)
	{
		ft_putstr("matrix is NULL\n");
		return;
	}

	int i, j;
	for (i = 0; i < r; i++)
	{
		if (!matrix[i])
			return;
		print_array_int(matrix[i], c);
	}
	ft_putstr("size=( ");
	ft_putnbr(r);
	ft_putstr(", ");
	ft_putnbr(c);
	ft_putstr(" )\n");
}

void print_array_int(int *arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		ft_putnbr(arr[i]);
		ft_putstr((i == n - 1) ? "\n" : " ");
	}
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

int write_to_file(int **matrix, int n, char const *filename)
{
	FILE *fp;
	int i, j;

	if (!matrix)
		return (-2);

	fp = fopen(filename, "w");
	if (!fp)
	{
		ft_putstr("Failed to open file.\n");
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
