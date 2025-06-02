#include "lib.h"

/**
 * @brief Converts an adjacency matrix to a vertex list representation
 *
 * Creates a list of vertices with incident edges based on the adjacency matrix.
 * The returned structure can be used with algo_euler and other functions
 * expecting the vertex-edge list representation.
 *
 * @param matrix Adjacency matrix (n x n)
 * @param n Number of vertices
 * @param undirected 1 if undirected, 0 if directed
 * @return Array of Vertex pointers, or NULL on failure
 */
Vertex      **adj_matrix_to_vertices(int **matrix, int n, int undirected)
{
    Vertex **vertices;
    int edge_id;
    int i, j;

    vertices = create_vertex_array(n);
    if (!vertices)
        return (NULL);
    edge_id = 0;
    for (i = 0; i < n; i++)
    {
        if (undirected)
        {
            for (j = i + 1; j < n; j++)
                if (matrix[i][j])
                    add_undirected_edge(vertices, i, j, edge_id++);
        }
        else
            for (j = 0; j < n; j++)
                if (matrix[i][j])
                    add_directed_edge(vertices, i, j, edge_id++);
    }
    return vertices;
}

/**
 * @brief Converts a vertex list representation to an adjacency matrix
 *
 * @param vertices Array of Vertex pointers
 * @param n Number of vertices
 * @return Adjacency matrix, or NULL on failure
 */
int **vertices_to_adj_matrix(Vertex **vertices, int n)
{
    int **matrix;
    Edge *edge;
    int i;

    matrix = generate_matrix(n, n);
    if (!matrix)
        return (NULL);
    for (i = 0; i < n; i++)
    {
        edge = vertices[i]->incidence;
        while (edge)
        {
            matrix[edge->from][edge->to] = 1;
            if (edge->from != edge->to)
                matrix[edge->to][edge->from] = 1;
            edge = edge->next;
        }
    }

    return matrix;
}

int **comp_adj_matrix(int **matrix, int n)
{
    int **comp;
    int i, j;

    comp = generate_matrix(n, n);
    if (!comp)
        return NULL;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j) continue;
            comp[i][j] = 1 - matrix[i][j];
        }
    }
    return comp;
}

Vertex **comp_adj_list(int **matrix, int n, int undir)
{
    Vertex **comp_list;
    int **comp;

    comp = comp_adj_matrix(matrix, n);
    if (!comp)
        return NULL;
    comp_list = adj_matrix_to_vertices(comp, n, undir);

    free_matrix_int(comp, n, n);
    return comp_list;
}
