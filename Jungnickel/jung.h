#ifndef JUNG_H
#define JUNG_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 1-2-16: プルーファーコードから次数列を計算
int *count_degrees(int *prufer, int n);

// 1-2-17: 次数列からプルーファーコードを生成
int *generate_prufer_code(int *degrees, int n);

// 1-2-17-2: 次数列から隣接行列を生成
int **generate_matrix(int *degs, int n);

// print_graph: 隣接行列からグラフを描画
void draw_graph(int **matrix, int n);

// is_tree: 隣接行列が木を表しているか判定
int is_tree(int **matrix, int n);

// ユーティリティ関数: 最小次数頂点を見つける
int find_min_vertex(int *degs, int n);

// ユーティリティ関数: 最大次数頂点を見つける
int find_max_vertex(int *degs, int n, int exclude);

// ユーティリティ関数: プルーファーコードで次に使用する最小頂点を見つける
int find_min(int *prufer, int *appeared, int vertices, int n, int current_index);

#endif