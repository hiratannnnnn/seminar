#include "lib.h"

size_t mem = 0;
size_t mem_peak = 0;

int main(void)
{
	int **matrix;
	int **line_graph;
	int n = 12;
	int len;

	len = 0;
	matrix = generate_random_graph(n, 0.1);
	if (!matrix)
		return (1);
	Vertex **vs;
	vs = adj_matrix_to_vertices(matrix, n, 1);
	line_graph = line_graph_from_adj_list(vs, n, &len, 1);
	print_matrix(matrix, n, n);
	print_matrix(line_graph, len, len);

	free_matrix_int(matrix, n, n);
	free_matrix_int(line_graph, len, len);
	free_vertex_array(vs, n);

	print_mem_peak();
	return (0);
}
