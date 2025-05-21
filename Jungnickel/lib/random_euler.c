#include "lib.h"

/**
 * @brief Makes a graph Eulerian by ensuring all vertices have even degree
 *
 * @param matrix Adjacency matrix to modify
 * @param n Number of vertices
 * @return 1 if successful, 0 if failed
 */
int make_eulerian(int **matrix, int n)
{
    // Allocate working memory
    int *degree = (int *)malloc(n * sizeof(int));
    int *odd_list = (int *)malloc(n * sizeof(int));
    if (!degree || !odd_list) {
        if (degree) free(degree);
        if (odd_list) free(odd_list);
        return 0;
    }

    // Find odd degree vertices
    compute_degrees(matrix, n, degree);
    int odd_count = find_odd_vertices(degree, n, odd_list);

    // Make graph Eulerian
    int result = pair_odd_vertices(matrix, n, odd_list, odd_count);

    // Clean up
    free(degree);
    free(odd_list);

    return result;
}

/**
 * @brief Generates a random connected Eulerian graph
 *
 * Creates a graph where all vertices have even degree, ensuring
 * it is Eulerian. The graph is guaranteed to be connected.
 *
 * @param n Number of vertices
 * @return Pointer to the generated adjacency matrix (n, n)
 *         or NULL on failure
 */
int **generate_random_euler(int n)
{
    int **matrix;
    int *prufer;
    int *degree;

    if (n < 3) return NULL;

    // Random seed
    srand(time(NULL) + clock());

    // Initialization
    prufer = generate_random_prufer(n);
    if (!prufer) return NULL;

    degree = count_degrees_from(prufer, n);
    if (!degree) {
        free(prufer);
        return NULL;
    }

    matrix = generate_matrix(n, n);
    if (!matrix) {
        free(prufer);
        free(degree);
        return NULL;
    }
    // End initialization

    // Create tree structure
    build_tree_from(matrix, prufer, degree, n);
    if (write_to_file(matrix, n, "tree_graph.txt") < 0)
        printf("Warning: Failed to write tree graph to file\n");

    // Make graph Eulerian
    if (!make_eulerian(matrix, n)) {
        printf("Warning: Failed to make the graph Eulerian\n");
    }

    // randomly append cycles
    int max_edges = n * (n - 1) / 2;
    int current_edges = sum_matrix(matrix, n, n) / 2;
    int remaining_edges = max_edges - current_edges;
    int trials = 0;
    int max_trials = n * 10;

    while (remaining_edges > 0 && trials < max_trials)
    {
        double prob = (double)remaining_edges / max_edges;
        if ((rand() / (double)RAND_MAX) < prob)
        {
            int v = rand() % n;
            if (make_cycle(matrix, n, v))
            {
                current_edges = sum_matrix(matrix, n, n) / 2;
                remaining_edges = max_edges - current_edges;
            }
        }
        else
            break;
        trials++;
    }

    // Save result
    if (write_to_file(matrix, n, "euler_graph.txt") < 0) {
        printf("Warning: Failed to write Euler graph to file\n");
    }

    // Clean up
    free(prufer);
    free(degree);

    return matrix;
}
