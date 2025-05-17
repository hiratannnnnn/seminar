#include "../jung.h"

static void	dfs(int **matrix, int n, int vertex, int *visited);

/**
 * @brief Determines if the given adjacency matrix represents a tree.
 *
 * A tree is defined as a connected,
	acyclic graph with n vertices and n-1 edges.

	* This function checks if the number of edges is n-1 and if the graph is connected
 * by performing a depth-first search (DFS) from vertex 0.
 *
 * @param matrix Pointer to the 2D adjacency matrix (size n x n)
 * @param n Number of vertices (size of the matrix)
 * @return 1 if the matrix represents a tree, 0 otherwise
 */

int	is_tree(int **adj, int n)
{
	int	edge_count;
	int	*visited;

	edge_count = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (adj[i][j])
				edge_count++;
	if (edge_count != n - 1)
		return (0);
	visited = (int *)calloc(n, sizeof(int));
	dfs(adj, n, 0, visited);
	for (int i = 0; i < n; i++)
	{
		if (!visited[i])
		{
			free(visited);
			return (0);
		}
	}
	free(visited);
	return (1);
}

static void	dfs(int **matrix, int n, int vertex, int *visited)
{
	visited[vertex] = 1;
	for (int i = 0; i < n; i++)
		if (matrix[vertex][i] && !visited[i])
			dfs(matrix, n, i, visited);
}
