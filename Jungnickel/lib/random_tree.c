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

int	*generate_random_prufer(int n)
{
	int i;

	if (n < 2)
		return NULL;
	int *prufer = (int *)malloc((n - 2) * sizeof(int));
	if (!prufer)
		return NULL;
	for (i = 0; i < n - 2; i++)
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
		degree[prufer[i]]++;
	return degree;
}

/**
 * @brief Generates a random undirected adjacency matrix of TREE
 * and writes it to a file.
 *
 * HAS TO BE FREED
 *
 * @param n Number of vertices
 * @return Pointer to the generated adjacency matrix (n, n),
 * 			or NULL on failure.
 */

int **generate_random_tree(int n)
{
	int **matrix;
	int *prufer, *degree;
	int i, j;

	// initialization
	matrix = generate_matrix(n, n);
	if (!matrix)
		return NULL;
	srand((unsigned int)time(NULL));
	prufer = generate_random_prufer(n);
	if (!prufer)
	{
		free_array_int(matrix, n);
		return NULL;
	}
	degree = count_degrees_from(prufer, n);
	if (!degree)
	{
		free(prufer);
		free_array_int(matrix, n);
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

	free(prufer);
	free(degree);
	return matrix;
	// free_array_int(matrix, n);
}

/**
 * @brief Builds a tree from a Prufer code into the adjacency matrix
 * 
 * @param matrix Adjacency matrix to build into
 * @param prufer Prufer code array
 * @param degree Working array for vertex degrees
 * @param n Number of vertices
 */
void build_tree_from(int **matrix, int *prufer, int *degree, int n)
{
    int i, j, u = -1, v = -1;
    
    // Process Prufer code
    for (i = 0; i < n - 2; i++) {
        for (j = 0; j < n; j++) {
            if (degree[j] == 1) {
                matrix[j][prufer[i]] = matrix[prufer[i]][j] = 1;
                degree[j]--;
                degree[prufer[i]]--;
                break;
            }
        }
    }
    
    // Connect last two vertices
    for (i = 0; i < n; i++) {
        if (degree[i] == 1) {
            if (u == -1) u = i;
            else v = i;
        }
    }
    
    if (u != -1 && v != -1) {
        matrix[u][v] = matrix[v][u] = 1;
    }
}
