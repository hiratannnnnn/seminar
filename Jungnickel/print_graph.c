#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 隣接行列からグラフを簡易的に描画する関数
void draw_graph(int **matrix, int n)
{
    // 最大サイズを定義
    int max_width = 60;
    int max_height = 20;
    
    // 格子状に頂点を配置するための計算
    int cols = (int)sqrt(n) + 1;
    int rows = (n + cols - 1) / cols;
    
    // 各頂点の位置を計算
    int **positions = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        positions[i] = (int *)malloc(sizeof(int) * 2);
        positions[i][0] = (i % cols) * 8 + 4;  // x座標
        positions[i][1] = (i / cols) * 4 + 2;  // y座標
    }
    
    // 描画用の文字配列
    char **grid = (char **)malloc(sizeof(char *) * max_height);
    for (int i = 0; i < max_height; i++) {
        grid[i] = (char *)malloc(sizeof(char) * (max_width + 1));
        for (int j = 0; j < max_width; j++) {
            grid[i][j] = ' ';
        }
        grid[i][max_width] = '\0';
    }
    
    // エッジを描画
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (matrix[i][j]) {
                int x1 = positions[i][0];
                int y1 = positions[i][1];
                int x2 = positions[j][0];
                int y2 = positions[j][1];
                
                // 単純な直線描画
                if (x1 == x2) {
                    // 垂直線
                    for (int y = y1 < y2 ? y1 : y2; y <= (y1 > y2 ? y1 : y2); y++) {
                        if (y >= 0 && y < max_height && x1 >= 0 && x1 < max_width) {
                            grid[y][x1] = '|';
                        }
                    }
                } else if (y1 == y2) {
                    // 水平線
                    for (int x = x1 < x2 ? x1 : x2; x <= (x1 > x2 ? x1 : x2); x++) {
                        if (y1 >= 0 && y1 < max_height && x >= 0 && x < max_width) {
                            grid[y1][x] = '-';
                        }
                    }
                } else {
                    // 斜め線
                    grid[(y1+y2)/2][(x1+x2)/2] = '\\';
                }
            }
        }
    }
    
    // 頂点を描画
    for (int i = 0; i < n; i++) {
        int x = positions[i][0];
        int y = positions[i][1];
        if (y >= 0 && y < max_height && x >= 0 && x < max_width) {
            grid[y][x] = '0' + ((i + 1) % 10);  // 頂点番号（1-indexed）
        }
    }
    
    // グラフを出力
    printf("\nGraph Visualization:\n");
    for (int i = 0; i < max_height; i++) {
        printf("%s\n", grid[i]);
    }
    
    // メモリ解放
    for (int i = 0; i < n; i++) {
        free(positions[i]);
    }
    free(positions);
    
    for (int i = 0; i < max_height; i++) {
        free(grid[i]);
    }
    free(grid);
}

// メイン関数に以下を追加
// draw_graph(matrix, n);