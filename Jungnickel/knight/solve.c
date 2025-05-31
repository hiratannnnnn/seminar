#include "knight.h"

void	solve_knight(int const r, int const c)	// <- main.c
{
	int **matrix;
	Vertex **vs;
	int n;

	n = r * c;
	matrix = generate_matrix(n, n);
	if (!matrix)
		return ;
	set_board_knight(matrix, r, c);		// -> board_init.c
	vs = adj_matrix_to_vertices(matrix, n, 1);
	if (!vs)
	{
		free_matrix_int(matrix, n, n);
		return ;
	}
	if (find_hamilton_cycle(vs, n))
		printf("FOUND hamilton cycle for (%d, %d).\n", r, c);
	else
		printf("there's no hamilton cycle for (%d, %d).\n", r, c);

	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
}
