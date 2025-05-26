#include "lib.h"

/**
 * @brief Finds an alternate trail for two already connected vertices
 *
 * Used during constructing Eulerian graphs.
 *
 * @param matrix Adjacency matrix
 * @param n Number of vertices
 * @param v1 First vertex
 * @param v2 Second vertex
 * @return 1 if successful, 0 if failed
 */
int make_trail(int **matrix, int n, int v1, int v2)
{
    int *visited;
    PathNode *path;

    visited = xcalloc(n, sizeof(int));
    if (!visited)
        return (0);
    path = find_path_dfs(matrix, n, v1, v2, visited, NULL);
    if (path)
    {
        add_edges_along_path(matrix, path);
        free_path(path);
        xfree(visited, sizeof(int) * n);
        return (1);
    }
    matrix[v1][v2] = matrix[v2][v1] = 1;
    xfree(visited, sizeof(int) * n);
    return (0);
}

/**
 * @brief Finds and adds a cycle (length >= 3) starting and ending at v
 *
 * Used during constructing Eulerian graphs.
 *
 * @param matrix Adjacency matrix
 * @param n Number of vertices
 * @param v Vertex to start/end the cycle
 * @return 1 if successful, 0 if failed
 */
int make_cycle(int **matrix, int n, int v)
{
    int *visited;
    PathNode *cycle;

    visited = xcalloc(n, sizeof(int));
    if (!visited)
        return 0;
    cycle = find_cycle_dfs(matrix, n, v, v, visited, 0);
    if (cycle)
    {
        add_edges_along_path(matrix, cycle);
        free_path(cycle);
        xfree(visited, sizeof(int) * n);
        return 1;
    }
    xfree(visited, sizeof(int) * n);
    return 0;
}

/**
 * @brief Finds a common unconnected vertex for two vertices
 *
 * @param matrix Adjacency matrix
 * @param n Number of vertices
 * @param v1 First vertex
 * @param v2 Second vertex
 * @return 1 if successful, 0 if failed
 */
int find_common_vertex(int **matrix, int n, int v1, int v2)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (i != v1 &&                   // not v1, nor v2
            i != v2 && !matrix[v1][i] && // not connected
            !matrix[v2][i])
        {
            matrix[v1][i] = matrix[i][v1] = 1;
            matrix[v2][i] = matrix[i][v2] = 1;
            return (1);
        }
    }
    return (0);
}

/**
 * @brief Connects odd-degree vertex pairs to make the graph Eulerian
 *
 * @param matrix Adjacency matrix
 * @param n Number of vertices
 * @param odd_list List of odd-degree vertices
 * @param odd_count Number of odd-degree vertices
 * @return 1 if successful, 0 if failed
 */
int pair_odd_vertices(int **matrix, int n, int *odd_list, int odd_count)
{
    int i;
    int v1, v2;

    // adding edges
    if (odd_count % 2 != 0)
        return (0);
    for (i = 0; i < odd_count; i += 2)
    {
        v1 = odd_list[i];
        v2 = odd_list[i + 1];
        if (!matrix[v1][v2])
            matrix[v1][v2] = matrix[v2][v1] = 1;
        else if (!make_trail(matrix, n, v1, v2))
            if (!find_common_vertex(matrix, n, v1, v2))
                return (0);
    }
    // adding edges
    return (1);
}
