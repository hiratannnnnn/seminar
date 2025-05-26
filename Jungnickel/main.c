#include "./include/lib.h"

int 	main(void)
{
	int **matrix;
	int n;

	n = 12;
	matrix = generate_random_digraph(n, 0.5);
	if (!matrix)
		return (1);
	print_matrix(matrix, n, n);

	write_adjacent_list(matrix, n, "test_graph.txt");
	free_matrix_int(matrix, n, n);

	printf("\n");

	int num;
	matrix = read_list(&num, "test_graph.txt");
	if (!matrix)
		return (1);
	print_matrix(matrix, n, n);
	free_matrix_int(matrix, n, n);
	return (0);
}
