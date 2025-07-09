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

	n = 15;
	// matrix = generate_random_undigraph_dbcost(n, 30);
	matrix = generate_random_undigraph_intcost(n, 30);
	// print_matrix_double(matrix, n, n, 1);
	print_matrix_int(matrix, n, n);
	vs = adj_matrix_to_vertices(matrix, n, 0);
	// print_vertices(vs, n);

	solve(vs, n);
	solve_prim(vs, n);
	// free

	// free_matrix_double(matrix, n, n);
	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	proc_end = clock();
	print_info();
	return (0);
}
