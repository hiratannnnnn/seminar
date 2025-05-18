#include "../jung.h"

/**
 * @brief Returns the degree of each vertex based on the adjacency matrix
 * 
 * @param matrix The adjacency matrix
 * @param n Number of vertices
 * @param degree Array to store degree values
 */
void compute_degrees(int **matrix, int n, int *degree)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        degree[i] = 0;
        for (j = 0; j < n; j++)
            if (matrix[i][j])
                degree[i]++;
    }
}

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

/**
 * @brief Identifies vertices with odd degree and stores them in odd_list
 * 
 * @param degree Array of vertex degrees
 * @param n Number of vertices
 * @param odd_list Array to store indices of odd-degree vertices
 * @return Number of odd-degree vertices found
 */
int find_odd_vertices(int *degree, int n, int *odd_list)
{
    int i, odd_count = 0;

    for (i = 0; i < n; i++)
        if (degree[i] % 2 == 1)
            odd_list[odd_count++] = i;

    return odd_count;
}
