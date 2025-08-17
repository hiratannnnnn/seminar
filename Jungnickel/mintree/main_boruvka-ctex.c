// filepath: /c/Users/PC_User/seminar/Jungnickel/mintree/main.c
#include "mintree.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

// 

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	int **matrix;
	Vertex **vs;
	int n;

	matrix = read_adj(&n, "boruvka_ctex.txt");
	vs = adj_matrix_to_vertices(matrix, n, 0);

	for (int i = 0; i < n; i++)
		sort_list(&vs[i]->incidence, cmp_int_asc);

	printf("\nConducting Boruvka Error-case for graphs having some same weights.\n\n");
	print_matrix_int(matrix, n, n);
	print_vertices(vs, n);
	reset_labels(vs, n);
	solve_boruvka(vs, n);

	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	print_info();
	return (0);
}
