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

	n = 30;
	matrix = gen_rand_conn_undigraph(n, 0.6);
	// matrix = read_adj(&n, "bfs_graph.txt");
	// write_adjacent_matrix(matrix, n, "bfs_graph.txt");
	vs = adj_matrix_to_vertices(matrix, n, 1);

	print_info();

	solve_bfs(vs, 0, n);
	solve_bipart(vs, 0, n);

	// free
	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);

	print_info();
	return (0);
}
