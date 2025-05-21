#include "lib.h"

/**
 * @brief Reads an adjacency matrix from a file.
 *
 * The file should have the number of vertices n in the first line,
 * followed by n lines each containig n integers (0 or 1) separated by spaces.
 *
 * the length of lines and cols of the file must be the same.
 *
 * @param *n pointer to the size n
 * @param filename The name of the file to read from
 * @return Pointer to the allocated 2D adjacency matrix, or NULL on failure.
 */

int **read_adj(int *n, char const *filename)
{
	FILE *fp;
	int **matrix;
	int i, j;

	// opening file
	fp = fopen(filename, "r");
	if (!fp)
		return NULL;
	// opening file

	// set size n
	if (fscanf(fp, "%d", n) != 1)
	{
		fclose(fp);
		return NULL;
	}
	// set size n

	// initialize matrix
	matrix = generate_matrix(*n, *n);
	if (!matrix)
	{
		fclose(fp);
		return NULL;
	}
	// initialize matrix *** has to be freed

	// set matrix
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *n; j++)
		{
			if (fscanf(fp, "%d", &matrix[i][j]) != 1)
			{
				free_array_int(matrix, i);
				fclose(fp);
				return NULL;
			}
		}
	}
	// set matrix

	fclose(fp);
	return matrix;
}	// *** has to be freed
