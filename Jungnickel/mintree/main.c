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

	double **matrix;
	Vertex **vs;
	Node *head;
	int n;

	n = 12;
	matrix = generate_random_digraph_dbcost(n, 30);
	print_matrix_double(matrix, n, n, 1);
	vs = cost_matrix_to_vertices(matrix, n, 0);
	print_vertices(vs, n);

	solve(vs, &head);

	// free

	free_matrix_double(matrix, n, n);
	free_vertex_array(vs, n);
	proc_end = clock();
	print_info();
	return (0);
}
