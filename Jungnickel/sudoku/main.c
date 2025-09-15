// filepath: $(pwd)/sudoku/main.c
#include "sudoku.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	int **board;
	int n;

	n = 9;
	// board = gen_matrix_int(n, n);
	board = read_adj(&n, "prob.txt");

	solve_sudoku(board, n);

	// free
	free_matrix_int(board, n, n);
	print_info();
	return (0);
}
