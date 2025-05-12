#include <stdio.h>
#include <stdlib.h>

// 0-indexedの内部表現を使用し、find_min関数は変更なし
int find_min(int *prufer, int *appeared, int vertices, int n, int current_index)
{
    int *frequency = (int *)malloc(sizeof(int) * vertices);
    for (int i = 0; i < vertices; i++)
        frequency[i] = 0;

    for (int i = current_index; i < n; i++)
        frequency[prufer[i]]++;

    for (int i = 0; i < vertices; i++)
    {
        if (appeared[i] == 0 && frequency[i] == 0)
        {
            appeared[i] = 1;
            free(frequency);
            return i;
        }
    }

    free(frequency);
    return -1;
}

int *count_degrees(int *prufer, int n)
{
    int i;
    int *degrees;
    int *appeared;
    int vertices = n + 2;

    // 配列の初期化
    degrees = (int *)malloc(sizeof(int) * vertices);
    for (i = 0; i < vertices; i++)
        degrees[i] = 1; // 木では各頂点は少なくとも1つのエッジを持つ
    
    appeared = (int *)malloc(sizeof(int) * vertices);
    for (i = 0; i < vertices; i++)
        appeared[i] = 0;

    // デバッグ用出力 (1-indexedで表示)
    printf("Prufer code: ");
    for (i = 0; i < n; i++)
        printf("%d ", prufer[i] + 1); // 表示用に+1
    printf("\n");

    // プルーファーコードの処理
    for (i = 0; i < n; i++)
    {
        int min = find_min(prufer, appeared, vertices, n, i);
        printf("Step %d: min=%d, prufer[%d]=%d\n", 
               i + 1, min + 1, i + 1, prufer[i] + 1); // 表示用に+1
        
        if (min != -1) {
            degrees[prufer[i]]++; // プルーファーコードに現れる頂点の次数を+1
        } else {
            printf("Error: find_min returned -1\n");
        }
    }

    // 最後に残った頂点の処理
    int min1 = find_min(prufer, appeared, vertices, n, n);
    int min2 = find_min(prufer, appeared, vertices, n, n);
    printf("Final vertices: min1=%d, min2=%d\n", 
           min1 != -1 ? min1 + 1 : -1, min2 != -1 ? min2 + 1 : -1); // 表示用に+1
    
    free(appeared);
    return degrees;
}
int main(int argc, char *argv[])
{
    int n;
    int *prufer;
    int *degrees;
    int vertices;
    int i;

    if (argc < 2) {
        // デフォルトの場合
        int prufer_1indexed[] = {4, 4, 4, 5}; // 1-indexedでの値
        n = sizeof(prufer_1indexed) / sizeof(prufer_1indexed[0]);
        
        prufer = (int *)malloc(sizeof(int) * n);
        for (i = 0; i < n; i++) {
            prufer[i] = prufer_1indexed[i] - 1; // 内部処理用に-1
        }
    } else {
        // コマンドライン引数がある場合
        n = argc - 1;
        prufer = (int *)malloc(sizeof(int) * n);
        for (i = 0; i < n; i++) {
            prufer[i] = atoi(argv[i+1]) - 1; // 1-indexedから0-indexedに変換
        }
    }

    vertices = n + 2;

    degrees = count_degrees(prufer, n);

    printf("頂点の次数:\n");
    for (i = 0; i < vertices; i++)
    {
        printf("頂点 %d: %d\n", i + 1, degrees[i]);
    }

    free(degrees);
    free(prufer);
    return 0;
}