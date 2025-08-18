// filepath: /c/Users/PC_User/seminar/Jungnickel/sorting/main.c
#include "sorting.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
	proc_start = clock();

	int **matrix;
	Vertex **vs;
	int n, i;
	int *degree;

	n = 15;
	matrix = gen_rand_undigraph(n, 0.7);
	vs = adj_matrix_to_vertices(matrix, n, 1);
	print_matrix_int(matrix, n, n);
	print_vertices(vs, n, 0);

	degree = (int *)xmalloc(sizeof(int) * n);
	compute_degrees(matrix, n, degree);
	print_array_int(degree, n, 0);
	for (i = 0; i < n; i++)
	{
		// sort_list(&vs[i]->incidence, cmp_smaller);
		sort_list_by_degree(&vs[i]->incidence, degree, cmp_smaller);
	}

	print_vertices(vs, n, 0);

	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	free_array_int(degree, n);
	print_info();
	return (0);
}
