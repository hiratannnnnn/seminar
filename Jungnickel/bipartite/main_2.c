#include "bipartite.h"

/**
 * @brief main function for the 2nd question of the report
 * @param a2.txt
 * 左上から、左下に斜めに0, 1, 2, と頂点番号をつけていったときの、二部グラフの隣接行列。
 * 通常の隣接行列ではなく、不要な部分をカットした二部グラフ専用の構成にしている。
 *
 */
int main(void)
{
	proc_start = clock();

	int **matrix;
	int *match_to;
	int a, b;

	matrix = read_matrix(&a, &b, "a2.txt");
	match_to = (int *)xcalloc(b, sizeof(int));
	printf("%d\n", max_bipartite_matching(matrix, a, b, match_to));
	free_matrix_int(matrix, a, b);
	free_array_int(match_to, b);

	proc_end = clock();
	// print_info();
	return (0);
}
