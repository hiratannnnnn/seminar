// 1-2-17-2.c
// generate_matrix by minmax

#include <stdio.h>
#include <stdlib.h>

/**
 * @todo カスみたいな実装を改良します
 */

int find_min_vertex(int *degs, int n)
{
    int min_v = -1;
    int min_d = 1000000;

    for (int i = 0; i < n; i++)
    {
        if (degs[i] > 0 && degs[i] < min_d)
        {
            min_d = degs[i];
            min_v = i;
        }
    }
    return min_v;
}

int find_max_vertex(int *degs, int vertices, int exclude)
{
    int max_v = -1;
    int max_d = -1;

    for (int i = 0; i < vertices; i++)
    {
        if (i != exclude && degs[i] > 0 && degs[i] > max_d)
        {
            max_d = degs[i];
            max_v = i;
        }
    }
    return max_v;
}

int **generate_matrix_from_degree(int *degs, int n)
{
    // 最初の次数を保存（デバッグ用）
    int *orig_degs = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        orig_degs[i] = degs[i];

    int *temp = (int *)malloc(sizeof(int) * n);
    int **matrix = (int **)malloc(sizeof(int *) * n);

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        temp[i] = degs[i];
    }

    int edges = 0;

    // n-1本の辺を確実に生成する
    while (edges < n - 1)
    {
        // 次数が正の頂点のうち、最小の次数を持つ頂点を見つける
        int min_v = find_min_vertex(temp, n);
        if (min_v == -1)
        {
            printf("Error: No vertex with positive degree found.\n");
            break;
        }

        // 最小頂点以外で、次数が正の頂点のうち、最大の次数を持つ頂点を見つける
        int max_v = find_max_vertex(temp, n, min_v);
        if (max_v == -1)
        {
            printf("Error: No second vertex with positive degree found.\n");
            break;
        }

        // まだ接続されていない場合のみ接続
        if (matrix[min_v][max_v] == 0)
        {
            matrix[min_v][max_v] = 1;
            matrix[max_v][min_v] = 1;

            temp[min_v]--;
            temp[max_v]--;

            edges++;

            printf("Edge %d: Connected %d and %d (degrees: %d, %d)\n", edges, min_v + 1, max_v + 1, temp[min_v] + 1,
                   temp[max_v] + 1);
        }
        else
        {
            // すでに接続されている場合、アルゴリズムを見直す必要がある
            printf("Warning: Vertices %d and %d are already connected.\n", min_v + 1, max_v + 1);

            // 0にするのではなく、1減らして次の候補を探す
            if (temp[min_v] > 0)
                temp[min_v]--;
            else if (temp[max_v] > 0)
                temp[max_v]--;
            else
            {
                // 両方0なら探索終了
                printf("Error: Cannot create more edges. Graph may not be "
                       "constructible with this algorithm.\n");
                break;
            }
        }

        // グラフの連結性を確保するための検証
        int remaining_vertices = 0;
        for (int i = 0; i < n; i++)
        {
            if (temp[i] > 0)
                remaining_vertices++;
        }

        if (remaining_vertices < 2 && edges < n - 1)
        {
            printf("Warning: Not enough vertices with positive degree "
                   "remaining, but only %d edges created.\n",
                   edges);
            printf("Original degrees: ");
            for (int i = 0; i < n; i++)
                printf("%d ", orig_degs[i]);
            printf("\nCurrent degrees: ");
            for (int i = 0; i < n; i++)
                printf("%d ", temp[i]);
            printf("\n");
            break;
        }
    }

    free(temp);
    free(orig_degs);
    return matrix;
}

// int main(int argc, char *argv[])
// {
//     int n;
//     int *degs;
//     int **matrix;
//     int i, j, sum = 0;

//     if (argc < 2)
//     {
//         n = 6;
//         degs = (int *)malloc(sizeof(int) * n);
//         degs[0] = 1;
//         degs[1] = 1;
//         degs[2] = 1;
//         degs[3] = 4;
//         degs[4] = 2;
//         degs[5] = 1;
//     }
//     else
//     {
//         n = argc - 1;
//         degs = (int *)malloc(sizeof(int) * n);
//         for (i = 0; i < n; i++)
//             degs[i] = atoi(argv[i + 1]);
//     }

//     for (i = 0; i < n; i++)
//         sum += degs[i];

//     if (sum != 2 * (n - 1))
//     {
//         printf("Error: sum of degrees (%d) != 2(n-1) = %d\n", sum, 2 * (n -
//         1)); free(degs); return 1;
//     }

//     printf("Degrees: ");
//     for (i = 0; i < n; i++)
//         printf("%d ", degs[i]);
//     printf("\n");

//     matrix = generate_matrix(degs, n);

//     printf("\nAdjacency Matrix:\n");
//     for (i = 0; i < n; i++)
//     {
//         for (j = 0; j < n; j++)
//         {
//             printf("%d ", matrix[i][j]);
//         }
//         printf("\n");
//     }

//     // 実際の次数を検証（デバッグ用）
//     int *actual_degrees = (int *)malloc(sizeof(int) * n);
//     for (i = 0; i < n; i++) {
//         actual_degrees[i] = 0;
//         for (j = 0; j < n; j++) {
//             if (matrix[i][j] == 1) actual_degrees[i]++;
//         }
//     }

//     printf("\nActual degrees after graph construction:\n");
//     for (i = 0; i < n; i++) {
//         printf("Vertex %d: %d\n", i + 1, actual_degrees[i]);
//     }

//     free(actual_degrees);
//     for (i = 0; i < n; i++)
//     {
//         free(matrix[i]);
//     }
//     free(matrix);
//     free(degs);

//     return 0;
// }
