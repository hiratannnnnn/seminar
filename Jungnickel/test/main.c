#include "lib.h"

size_t mem = 0;
size_t mem_peak = 0;

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	printf("%d", count_digit(atoi(av[1])));
// 	return (0);
// }

int main(void)
{
	int **matrix;
	int **line_graph;
	char **names;
	int n = 12;
	int len;

	len = 0;
	matrix = generate_random_graph(n, 0.8);
	if (!matrix)
		return (1);
	Vertex **vs;
	vs = adj_matrix_to_vertices(matrix, n, 1);
	line_graph = line_graph_from_adj_list(vs, n, &names, &len, 1);
	print_matrix(matrix, n, n);
	print_matrix(line_graph, len, len);
	print_array_char(names, len);

	free_matrix_int(matrix, n, n);
	free_matrix_int(line_graph, len, len);
	free_vertex_array(vs, n);
	
	save_random_graph(n, 0.8, "random_graph.txt");

	matrix = read_adj(&n, "random_graph.txt");
	print_matrix(matrix, n, n);
	int **closure = closure_of(matrix, n);
	print_matrix(closure, n, n);
	free_matrix_int(matrix, n, n);
	free_matrix_int(closure, n, n);
	free_array_char(names, len);
	print_mem_peak();
	return (0);
}
