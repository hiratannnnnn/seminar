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

	matrix = read_adj(&n, "ex4414.txt");
	// shuffle_vertices(matrix, n);
	print_matrix_int(matrix, n, n);
	printf("is_undigraph: %d\n", is_undigraph(matrix, n));

	vs = adj_matrix_to_vertices(matrix, n, 0);
	print_vertices(vs, n, 0);
	for (int i = 0; i < n; i++)
		sort_list(&vs[i]->incidence, cmp_int_asc);

	printf("\n---------------------------\nConducting BORUVKA\n\n");
	proc_start = clock();
	solve_boruvka(vs, n, 1);
	reset_labels(vs, n);

	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	print_info();
	return (0);
}
