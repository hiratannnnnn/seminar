#include "lib.h"

/**
 * @brief Finds a path between two vertices using depth-first search
 *
 * @param matrix Adjacency matrix
 * @param n Number of vertices
 * @param current Current vertex being explored
 * @param end Target vertex, not equal to current
 * @param visited Array tracking visited vertices
 * @param path Current path being built
 * @param state caller should set state to 1
 * @return Path from current to end if found, NULL otherwise
 */
PathNode *find_path_dfs(
    int **matrix, int n, int current, int end, int *visited, PathNode *path)
{
    PathNode *result;
    PathNode *rest_path;
    PathNode *new_head;
    int i;

    if (current == end)
    {
        result = create_pathnode(current);
        if (!result)
            return NULL;
        return result;
    }

    visited[current] = 1;
    for (i = 0; i < n; i++)
    {
        if (((!visited[i] && !matrix[current][i]) || (i == end && !matrix[current][i])) && i != current)
        {
            rest_path = find_path_dfs(matrix, n, i, end, visited, path);
            if (rest_path)
            {
                new_head = create_pathnode(current);
                if (!new_head)
                {
                    PathNode *temp;
                    while (rest_path)
                    {
                        temp = rest_path;
                        rest_path = rest_path->next;
                        free(temp);
                    }
                    visited[current] = 0;
                    return NULL;
                }
                new_head->next = rest_path;
                visited[current] = 0;
                return new_head;
            }
        }
    }
    visited[current] = 0;
    return NULL;
}

PathNode *find_cycle_dfs(
    int **matrix, int n, int start, int current, int *visited, int depth)
{
    PathNode *result;
    PathNode *rest_path;
    PathNode *new_head;
    int i, offset;

    if (current == start && depth >= 2)
    {
        result = create_pathnode(current);
        if (!result)
            return NULL;
        return result;
    }

    visited[current] = 1;
    for (offset = 1; offset < n; offset++)
    {
        i = (current + offset) % n;
        if ((i == start && depth >= 2 && !matrix[current][i]) ||
            (!visited[i] && !matrix[current][i] && i != current))
        {
            rest_path = find_cycle_dfs(matrix, n, start, i, visited, depth + 1);
            if (rest_path)
            {
                new_head = create_pathnode(current);
                if (!new_head)
                {
                    PathNode *temp;
                    while (rest_path)
                    {
                        temp = rest_path;
                        rest_path = rest_path->next;
                        free(temp);
                    }
                    visited[current] = 0;
                    return NULL;
                }
                new_head->next = rest_path;
                visited[current] = 0;
                return new_head;
            }
        }
    }
    visited[current] = 0;
    return NULL;
}

// Add edges along the path found by DFS
void add_edges_along_path(int **matrix, PathNode *path)
{
    PathNode *current;
    PathNode *next;
    current = path;
    next = path->next;

    while (next)
    {
        matrix[current->vertex][next->vertex] = 1;
        matrix[next->vertex][current->vertex] = 1;

        current = next;
        next = next->next;
    }
}

// Free memory allocated for path
void free_path(PathNode *path)
{
    PathNode *temp;

    while (path)
    {
        temp = path;
        path = path->next;
        free(temp);
    }
}
