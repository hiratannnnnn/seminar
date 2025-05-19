#include "jung.h"

int main(int ac, char **av)
{
    int n;
    int **matrix;
    Vertex **vertices;
    Node *euler_tour;
    if (ac != 2)
        return (1);
    n = atoi(av[1]);

    matrix = generate_random_euler(n);
    if (!matrix)
        return (printf("Error generating graph\n"), 1);
    // printf("%d\n", sum_matrix(matrix, n, n));

    // print_matrix(matrix, n, n);
    vertices = adj_matrix_to_vertices(matrix, n);
    if (!vertices)
        return (free_array_int(matrix, n), 1);
    euler_tour = NULL;
    algo_euler(vertices, n, 0, &euler_tour);
    if (euler_tour)
    {
        // print_euler_tour_edges(euler_tour);
        // print_euler_tour_vertices(euler_tour, vertices);
        write_euler_tour_vertices(euler_tour, vertices, "euler_path.txt");
    }

    free_node_list(euler_tour);
    free_vertex_array(vertices, n);
    free_array_int(matrix, n);
    return (0);
}
