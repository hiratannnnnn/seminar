#include "lib.h"

size_t mem = 0;
size_t mem_peak = 0;

int main(void)
{
	int **matrix;
	int **cpy;
	int **closure;
	int const n = 12;

	matrix = generate_random_graph(n, 0.7);
	if (!matrix)
		return (1);
	cpy = copy_matrix(matrix, n, n);
	free_matrix_int(matrix, n, n);
	print_matrix(cpy, n, n);

	if (cpy)
	{
		closure = closure_of(cpy, n);
		print_matrix(closure, n, n);
		free_matrix_int(cpy, n, n);
		free_matrix_int(closure, n, n);
		print_mem_peak();
	}
	return (0);
}
