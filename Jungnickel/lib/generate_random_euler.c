#include "../jung.h"

/**
 * @brief Generates a random connected Eulerian graph (adj mat.) with n vertices.
 * 		  The graph is guaranteed to be connected and all degrees are even.
 *
 * HAS TO BE FREED
 *
 * @param n Number of vertices
 * @return Pointer to the generated adjacency matrix (n, n)
 * 			or NULL on failure.
 */

int **generate_random_euler(int n)
{
	int **matrix;
	int *prufer;
	int *degree;
	int *odd_list;
	int odd_count = 0;
	int i, j;

	if (n < 2)
		return NULL;

	// initialization
	prufer = generate_random_prufer(n);
	if (!prufer)
		return NULL;
	degree = count_degrees_from(prufer, n);
	if (!degree)
		return (free(prufer), NULL);
	matrix = generate_matrix(n, n);
	if (!matrix)
	{
		free(prufer);
		free(degree);
		return NULL;
	}
	// initialization

	// build the tree from the Prufer code
	for (i = 0; i < n - 2; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (degree[j] == 1)
			{
				matrix[j][prufer[i]] = 1;
				matrix[prufer[i]][j] = 1;
				degree[j]--;
				degree[prufer[i]]--;
				break;
			}
		}
	}
		// the last two nodes
	int u = -1;
	int v = -1;
	for (i = 0; i < n; i++)
	{
		if (degree[i] == 1)
		{
			if (u == -1) u = i;
			else v = i;
		}
	}
	if (u != -1 && v != -1)
	{
		matrix[u][v] = 1;
		matrix[v][u] = 1;
	}
		// the last two nodes
	// build the tree from the Prufer code

	if (write_to_file(matrix, n, "test_graph.txt") < 0) return NULL;

	odd_list = (int *)malloc(n * sizeof(int));
	if (!odd_list)
	{
		free(prufer);
		free(degree);
		free_array_int(matrix, n);
		return NULL;
	}
	odd_count = 0;
	for (i = 0; i < n; i++)
		if (degree[i] % 2 == 1)
			odd_list[odd_count++] = i;


	int a, b;
	while (odd_count >= 2)
	{
		int found = 0;
		for (i = 0; i < odd_count - 1 && !found; i++) {
			for (j = i + 1; j < odd_count && !found; j++) {
				a = odd_list[i];
				b = odd_list[j];
				if (matrix[a][b] == 0) {
					matrix[a][b] = 1;
					matrix[b][a] = 1;
					degree[a]++;
					degree[b]++;
					for (int k = j; k < odd_count - 1; k++)
						odd_list[k] = odd_list[k + 1];
					odd_count--;
					for (int k = i; k < odd_count - 1; k++)
						odd_list[k] = odd_list[k + 1];
					odd_count--;
					found = 1;
				}
			}
		}
		if (!found && odd_count >= 2) {
			a = odd_list[0];
			b = odd_list[1];
			int c = -1, d = -1;
			for (i = 0; i < n; i++) {
				if (degree[i] % 2 == 0 && i != a && i != b) {
					if (c == -1) c = i;
					else if (d == -1) d = i;
				}
			}
			if (c != -1 && d != -1) {
				matrix[a][c] = 1;
				matrix[c][a] = 1;
				matrix[b][d] = 1;
				matrix[d][b] = 1;
				degree[a]++;
				degree[b]++;
				degree[c]++;
				degree[d]++;
				for (int k = 1; k < odd_count - 1; k++)
					odd_list[k] = odd_list[k + 1];
				odd_count--;
				for (int k = 0; k < odd_count - 1; k++)
					odd_list[k] = odd_list[k + 1];
				odd_count--;
				if (degree[c] % 2 == 1)
					odd_list[odd_count++] = c;
				if (degree[d] % 2 == 1)
					odd_list[odd_count++] = d;
			} else {
				break;
			}
    	}
	}
	return matrix;
}
