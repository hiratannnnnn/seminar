// filepath: /c/Users/PC_User/seminar/Jungnickel/path/main.c
#include "path.h"

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
	Vertex **vs;
	int n;

	n = 5;
	// matrix = gen_rand_conn_undigraph(n, 0.6);
	matrix = gen_rand_undigraph_intcost(n, 30);
	// matrix = read_adj(&n, "bfs_graph.txt");
	// write_adjacent_matrix(matrix, n, "bfs_graph.txt");
	vs = adj_matrix_to_vertices(matrix, n, 1);
	print_matrix_int(matrix, n, n);
	matrix[0][1] = matrix[1][0] = -50;

	// solve_bfs(vs, 0, n);
	// solve_bipart(vs, 0, n);
	// solve_dijkstra(vs, 0, n);
	// solve_dijkstraPQ(vs, 0, n);
	// solve_bellford(vs, 0, n);
	// solve_floyd(matrix, n);
	solve_negacycle(matrix, n);

	// free
	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);

	print_info();
	return (0);
}
