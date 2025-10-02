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

	int **matrix;
	Vertex **vs;
	int n;

	n = 10;
	matrix = gen_rand_undigraph_intcost(n, 1, 30, 0.8);

	print_matrix_int(matrix, n, n);

	vs = adj_matrix_to_vertices(matrix, n, 0);

	print_vertices(vs, n, 0);

	printf("\n---------------------------\nConducting PRIM\n\n");
	proc_start = clock();
	solve_prim(vs, 0, n, 0);
	reset_labels(vs, n);	print_info();	sleep(3);

	printf("\n---------------------------\nConducting KRUSKAL\n\n");
	proc_start = clock();
	solve_kruskal(vs, n, 0);
	reset_labels(vs, n);	print_info();	sleep(3);

	printf("\n---------------------------\nConducting BORUVKA\n\n");
	proc_start = clock();
	solve_boruvka(vs, n, 0);
	reset_labels(vs, n);	print_info();

	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	print_info();
	return (0);
}
