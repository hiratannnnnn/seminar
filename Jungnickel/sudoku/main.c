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

	int **matrix;
	int n;

	n = 9;
	matrix = gen_matrix_int(n, n);

	solve_sudoku(matrix, n);

	// free
	free_matrix_int(matrix, n, n);
	print_info();
	return (0);
}
