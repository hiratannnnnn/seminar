// filepath: /Users/tomoyahirata/Documents/seminar/Jungnickel/test/main.c
#include "test.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	double **matrix;
	int n;

	n = 12;
	matrix = generate_random_digraph_dbcost(n, 30);
	print_matrix_double(matrix, n, n, 1);

	// free

	free_matrix_double(matrix, n, n);
	proc_end = clock();
	print_info();
	return (0);
}
