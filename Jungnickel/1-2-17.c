#include <stdio.h>
#include <stdlib.h>

// 次数が1の最小の頂点を見つける
int find_min_degree_one(int *degrees, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        if (degrees[i] == 1)
            return i;
    }
    return -1;
}

// 次数列からプルーファーコードを生成する
int *generate_prufer_code(int *degrees, int vertices)
{
    int n = vertices - 2; // プルーファーコードの長さ
    int *prufer = (int *)malloc(sizeof(int) * n);
    int *temp_degrees = (int *)malloc(sizeof(int) * vertices);
    
    // 次数の配列をコピー
    for (int i = 0; i < vertices; i++)
        temp_degrees[i] = degrees[i];
    
    // プルーファーコードを生成
    for (int i = 0; i < n; i++)
    {
        // 次数が1の最小の頂点を見つける
        int min = find_min_degree_one(temp_degrees, vertices);
        temp_degrees[min] = 0; // この頂点を使用済みとマーク
        
        // 次数が1より大きい最小の頂点を見つける
        int neighbor = -1;
        for (int j = 0; j < vertices; j++)
        {
            if (temp_degrees[j] > 1)
            {
                neighbor = j;
                break;
            }
        }
        
        // プルーファーコードに追加
        prufer[i] = neighbor;
        temp_degrees[neighbor]--; // 隣接頂点の次数を減らす
    }
    
    free(temp_degrees);
    return prufer;
}

int main(int argc, char *argv[])
{
    int vertices;
    int *degrees;
    int *prufer;
    int i;
    
    if (argc < 2)
    {
        // デフォルトの次数列: [1, 1, 1, 4, 2, 1]
        vertices = 6;
        degrees = (int *)malloc(sizeof(int) * vertices);
        degrees[0] = 1;
        degrees[1] = 1;
        degrees[2] = 1;
        degrees[3] = 4;
        degrees[4] = 2;
        degrees[5] = 1;
    }
    else
    {
        // コマンドライン引数から次数列を読み込む
        vertices = argc - 1;
        degrees = (int *)malloc(sizeof(int) * vertices);
        for (i = 0; i < vertices; i++)
            degrees[i] = atoi(argv[i + 1]);
    }
    
    // 次数列の表示
    printf("次数列: ");
    for (i = 0; i < vertices; i++)
        printf("%d ", degrees[i]);
    printf("\n");
    
    // プルーファーコードの生成
    prufer = generate_prufer_code(degrees, vertices);
    
    // プルーファーコードの表示
    printf("プルーファーコード: ");
    for (i = 0; i < vertices - 2; i++)
        printf("%d ", prufer[i] + 1); // 1-indexedで表示
    printf("\n");
    
    free(degrees);
    free(prufer);
    return 0;
}