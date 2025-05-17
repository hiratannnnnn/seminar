#include "../jung.h"

/**
 * @brief Generates a random Prufer code for a tree with n vertices.
 *
 * HAS TO BE FREED
 *
 * @param n Number of vertices
 * @return Pointer to the generated Prufer code (length n-2),
 * 			or NULL on failure.
 */

int	*generate_prufer_code(int n)
{
	int i;

	if (n < 2)
		return NULL;
	int *prufer = (int *)malloc((n - 2) * sizeof(int));
	if (!prufer)
		return NULL;
	for (i = 0; i < n; i++)
		prufer[i] = rand() % n;
	return prufer;
}

/**
 * @brief Generates the degree sequence from a Prufer code.
 *
 * HAS TO BE FREED
 *
 * @param prufer Pointer to the Prufer code (length n-2)
 * @param n Number of vertices
 * @return Pointer to the degree array (length n),
 * 			or NULL on failure.
 */

int *count_degrees_from(const int *prufer, int n)
{
	int i;

	int *degree = (int *)malloc(n * sizeof(int));
	if (!degree)
		return NULL;
	for (i = 0; i < n; i++)
		degree[i] = 1;
	for (i = 0; i < n - 2; i++)
		degree[prufer[i]]++;\
	return degree;
}

/**
 * @brief Generates a random undirected adjacency matrix of TREE
 * and writes it to a file.
 *
 * @param n Number of vertices
 * @param filename Output file name
 */

void generate_random_tree(int n, char const *filename)
{
	int **matrix;
	int *prufer, *degree;
	int i, j;

	// initialization
	matrix = generate_matrix(n, n);
	if (!matrix)
		return;
	// print_matrix(matrix, n, n);
	srand((unsigned int)time(NULL));
	prufer = generate_prufer_code(n);
	if (!prufer)
	{
		ft_putstr("Failed to allocate prufer code.\n");
		free_array_int(matrix, n);
		return;
	}
	degree = count_degrees_from(prufer, n);
	if (!degree)
	{
		ft_putstr("Failed to allocate degree array.\n");
		free(prufer);
		free_array_int(matrix, n);
		return;
	}
	// initialization

	print_array_int(degree, n);
	print_array_int(prufer, n-2);

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
	ft_putstr("debug: last two nodes\n");
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
	print_matrix(matrix, n, n);


	// build the tree from the Prufer code

	// write to file
	FILE *fp = fopen(filename, "w");
	if (!fp)
	{
		ft_putstr("Failed to open file.\n");
		free(prufer);
		free(degree);
		free_array_int(matrix, n);
		return;
	}
	fprintf(fp, "%d\n", n);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			fprintf(fp, "%d%c", matrix[i][j], (j == n - 1) ? '\n' : ' ');
	fclose(fp);
	// write to file

	free(prufer);
	free(degree);
	free_array_int(matrix, n);
}
