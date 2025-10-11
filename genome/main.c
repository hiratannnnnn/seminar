// filepath: $(pwd)/genome/main.c
#include "genome.h"

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

	n = 5;
	matrix = gen_matrix_int(n, n);
	printf("%d\n", count_breakpoints());

	print_matrix_int(matrix, n, n);
	// free

	print_info();
	return (0);
}
