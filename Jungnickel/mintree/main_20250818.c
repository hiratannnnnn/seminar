// filepath: /c/Users/PC_User/seminar/Jungnickel/mintree/main.c
#include "mintree.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	// double **matrix;
	int **matrix;
	Vertex **vs;
	int n;

	n = 10;
	// matrix = gen_rand_undigraph_dbcost(n, 0.0, 1.0, 0.8);
	matrix = gen_rand_undigraph_intcost(n, 1, 30, 0.8);

	// print_matrix_double(matrix, n, n, 1);
	// print_matrix_int(matrix, n, n);

	// vs = cost_matrix_to_vertices(matrix, n, 0);
	vs = adj_matrix_to_vertices(matrix, n, 0);

	// print_vertices(vs, n);
	printf("\nConducting KRUSKAL\n\n");
	reset_labels(vs, n);
	solve_kruskal(vs, n);
	reset_labels(vs, n);


	// free_matrix_double(matrix, n, n);
	free_matrix_int(matrix, n, n);

	free_vertex_array(vs, n);
	print_info();
	return (0);
}
