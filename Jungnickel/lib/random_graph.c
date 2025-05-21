#include "lib.h"

/**
 * @brief Generates a random undirected adjacency matrix and writes it to a file.
 *
 * @param n Number of vertices
 * @param edge_prob 0.0～1.0, edge probability between any two vertices
 * @param filename Output file name
 */

void generate_random_graph(int n, double edge_prob, char const *filename)
{
	int **matrix;
	int i, j;

	// initialization
	matrix = generate_matrix(n, n);
	// initialization

	// generate random matrix
	srand((unsigned int)time(NULL));
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if ((double)rand() / RAND_MAX < edge_prob)
			{
				matrix[i][j] = 1;
				matrix[j][i] = 1; // not for digraphs
			}
		}
	}
	// generate random matrix

	// write to file
	FILE *fp = fopen(filename, "w");
	if (!fp)
	{
		printf("Failed to open file.\n");
		free_array_int(matrix, n);
		return;
	}
	fprintf(fp, "%d\n", n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			fprintf(fp, "%d%c", matrix[i][j], (j == n - 1) ? '\n' : ' ');
	fclose(fp);
	free_array_int(matrix, n);
	// write to file
}
