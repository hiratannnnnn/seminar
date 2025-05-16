#include "../jung.h"

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

	result = (int **)malloc(sizeof(int *) * r);
	i = 0;
	while (i < r)
	{
		result[i] = (int *)malloc(sizeof(int) * c);
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
