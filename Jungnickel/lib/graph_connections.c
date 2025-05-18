#include "../jung.h"

/**
 * @brief Finds an alternate trail for two already connected vertices
 * 
 * @param matrix Adjacency matrix
 * @param n Number of vertices
 * @param v1 First vertex
 * @param v2 Second vertex
 * @return 1 if successful, 0 if failed
 */
int find_trail(int **matrix, int n, int v1, int v2)
{
    // Temporarily remove direct connection
    matrix[v1][v2] = 0;
    matrix[v2][v1] = 0;
    
    int *visited = calloc(n, sizeof(int));
    if (!visited) return 0;
    
    // Find alternate path
    PathNode *path = find_path_dfs(matrix, n, v1, v2, visited, NULL);
    
    if (path) {
        // Apply found path
        add_edges_along_path(matrix, path);
        free_path(path);
        free(visited);
        return 1;
    }
    
    // Restore edge if no path found
    matrix[v1][v2] = 1;
    matrix[v2][v1] = 1;
    free(visited);
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
    for (int j = 0; j < n; j++) {
        if (j != v1 && j != v2 && !matrix[v1][j] && !matrix[v2][j]) {
            // Connect both vertices to common vertex
            matrix[v1][j] = matrix[j][v1] = 1;
            matrix[v2][j] = matrix[j][v2] = 1;
            return 1;
        }
    }
    return 0;
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
    if (odd_count % 2 != 0) return 0;
    
    // Process pairs of odd-degree vertices
    for (int i = 0; i < odd_count; i += 2) {
        int v1 = odd_list[i];
        int v2 = odd_list[i + 1];
        
        if (!matrix[v1][v2]) {
            // Direct connection
            matrix[v1][v2] = 1;
            matrix[v2][v1] = 1;
        } else {
            // Try to find alternate trail
            if (!find_trail(matrix, n, v1, v2)) {
                // Try to connect through common vertex
                if (!find_common_vertex(matrix, n, v1, v2)) {
                    return 0;
                }
            }
        }
    }
    
    // Verify all vertices have even degree
    int *verify_degree = (int *)malloc(n * sizeof(int));
    if (!verify_degree) return 1; // Not critical, continue anyway
    
    compute_degrees(matrix, n, verify_degree);
    int remaining_odd = 0;
    
    for (int i = 0; i < n; i++) {
        if (verify_degree[i] % 2 == 1) {
            remaining_odd++;
        }
    }
    
    // Fix any remaining odd degree vertices
    if (remaining_odd > 0 && remaining_odd % 2 == 0) {
        int *odd_again = malloc(n * sizeof(int));
        if (odd_again) {
            int idx = 0;
            for (int i = 0; i < n; i++) {
                if (verify_degree[i] % 2 == 1) {
                    odd_again[idx++] = i;
                }
            }
            
            // Direct connect remaining odd vertices
            for (int i = 0; i < idx; i += 2) {
                int v1 = odd_again[i];
                int v2 = odd_again[i+1];
                matrix[v1][v2] = 1;
                matrix[v2][v1] = 1;
            }
            free(odd_again);
        }
    }
    
    free(verify_degree);
    return 1;
}
