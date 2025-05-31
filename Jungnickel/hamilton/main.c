#include "hamilton.h"

size_t 		mem = 0;
size_t 		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

/**
 * @brief look for hamilton cycle.
 */

int main(void)
{
	proc_start = clock();
	int **matrix;
	Vertex **vs;
	int n;

	n = 18;
	matrix = generate_random_graph(n, 0.4);
	write_adjacent_matrix(matrix, n, "a_graph.txt");
	vs = adj_matrix_to_vertices(matrix, n, 1);
	print_vertices(vs, n);
	printf("%d\n", solve(vs, n));

	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	proc_end = clock();
	print_info();
	return (0);
}

// int main(int ac, char **av)
// {
// 	if (ac != 3)
// 	{
// 		printf("Usage: ./a.out <r> <c>\n");
// 		return (1);
// 	}
// 	int r = atoi(av[1]);
// 	int c = atoi(av[2]);
// 	int **matrix = generate_matrix(r, c); // r * c


// 	print_info();
// 	return (0);
// }
