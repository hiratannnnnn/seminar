#include "lib.h"

/**
 * @brief make a closure of any adjacent matrix
 *
 * UNDIRECTED ONLY
 *
 * efficiency? complexity? rubbish.
 * @param matrix n * n matrix of int
 * @param n 	 n
 */
int 	**closure_of(int **matrix, int n)
{
	int **closure;
	int *degree;
	int done;
	int i, j;

	closure = copy_matrix(matrix, n, n);
	if (!closure)
		return (NULL);
	degree = (int *)xmalloc(sizeof(int) * n);
	if (!degree)
	{
		free_matrix_int(closure, n, n);
		return (NULL);
	}
	compute_degrees(closure, n, degree);
	done = 0;
	while (done == 0)
	{
		done = 1;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (i == j) continue;
				if ((degree[i] + degree[j] >= n) && !closure[i][j])
				{
					closure[i][j] = closure[j][i] = 1;
					degree[i]++;
					degree[j]++;
					done = 0;
				}
			}
		}
	}
	xfree(degree, sizeof(int) * n);
	return closure;
}
