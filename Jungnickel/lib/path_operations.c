#include "../jung.h"

/**
 * @brief Finds a path between two vertices using depth-first search
 * 
 * @param matrix Adjacency matrix
 * @param n Number of vertices
 * @param current Current vertex being explored
 * @param end Target vertex
 * @param visited Array tracking visited vertices
 * @param path Current path being built
 * @return Path from current to end if found, NULL otherwise
 */
PathNode *find_path_dfs(int **matrix, int n, int current, int end, 
    int *visited, PathNode *path)
{
// Base case: reached target vertex
if (current == end) {
PathNode *result = malloc(sizeof(PathNode));
if (!result) return NULL;

result->vertex = current;
result->next = NULL;
return result;
}

visited[current] = 1;

// Try all unvisited and unconnected vertices
for (int i = 0; i < n; i++) {
if (!visited[i] && !matrix[current][i]) {
PathNode *rest_path = find_path_dfs(matrix, n, i, end, visited, path);

if (rest_path) {
// Add current vertex to path
PathNode *new_head = malloc(sizeof(PathNode));
if (!new_head) {
// Memory allocation failed
PathNode *temp;
while (rest_path) {
temp = rest_path;
rest_path = rest_path->next;
free(temp);
}
return NULL;
}

new_head->vertex = current;
new_head->next = rest_path;
return new_head;
}
}
}

// No path found from this vertex
visited[current] = 0;
return NULL;
}


// Add edges along the path found by DFS
void add_edges_along_path(int **matrix, PathNode *path)
{
    PathNode *current = path;
    PathNode *next = path->next;
    
    while (next) {
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
    
    while (path) {
        temp = path;
        path = path->next;
        free(temp);
    }
}

