// filepath: /c/Users/PC_User/seminar/Jungnickel/test/main.c
#include "test.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
	proc_start = clock();

	int **matrix;
	Vertex **vs;
	int n;

	n = 24;

	matrix = generate_random_undigraph(n, 0.35);
	if (!matrix)
		return (1);
	vs = adj_matrix_to_vertices(matrix, n, 1);
	if (!vs)
	{
		free_matrix_int(matrix, n, n);
		return (1);
	}
	if (find_hamilton_cycle(vs, n))
		printf("happy\n");
	else
		printf("sad\n");
	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	proc_end = clock();
	print_info();
	return (0);
}
