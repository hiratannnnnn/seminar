#include <stdio.h>
#include <stdlib.h>
#include "../jung.h"

static void dfs(int **matrix, int n, int vertex, int *visited) {
    visited[vertex] = 1;

    for (int i = 0; i < n; i++) {
        if (matrix[vertex][i] && !visited[i]) {
            dfs(matrix, n, i, visited);
        }
    }
}

int is_tree(int **matrix, int n) {
    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j]) {
                edge_count++;
            }
        }
    }

    if (edge_count != n - 1) {
        return 0;
    }

    int *visited = (int *)calloc(n, sizeof(int));
    dfs(matrix, n, 0, visited);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            free(visited);
            return 0;
        }
    }

    free(visited);
    return 1;
}

void test_is_tree(int **matrix, int n) {
    printf("\n隣接行列が木を表しているかの検証:\n");

    printf("隣接行列:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    int edge_count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j]) {
                edge_count++;
            }
        }
    }

    printf("頂点数: %d\n", n);
    printf("エッジ数: %d\n", edge_count);

    if (is_tree(matrix, n)) {
        printf("結果: この隣接行列は木を表しています。\n");
    } else {
        printf("結果: この隣接行列は木ではありません。\n");
    }
}
