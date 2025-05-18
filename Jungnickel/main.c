#include "jung.h"

int main(void)
{
    int n = 12;
    int **matrix;
    Vertex **vertices;
    Node *euler_tour = NULL;

    // ランダムなオイラーグラフを生成
    matrix = generate_random_euler(n);
    if (!matrix) {
        printf("Error generating graph\n");
        return 1;
    }

    // 隣接行列を表示
    print_matrix(matrix, n, n);

    // 頂点表現に変換
    vertices = adj_matrix_to_vertices(matrix, n);
    if (!vertices) {
        free_array_int(matrix, n);
        return 1;
    }

    // オイラーツアーを探索
    algo_euler(vertices, n, 0, &euler_tour);

    // オイラーツアーを表示
    if (euler_tour) {
        print_euler_tour_edges(euler_tour);
        print_euler_tour_vertices(euler_tour, vertices);
    }

    // 後処理
    free_node_list(euler_tour);
    free_vertex_array(vertices, n);
    free_array_int(matrix, n);

    return 0;
}