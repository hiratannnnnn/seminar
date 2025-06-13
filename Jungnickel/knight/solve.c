#include "knight.h"

void	solve_knight(int const r, int const c)	// <- main.c
{
	int **matrix;
	Vertex **vs;
	int n;
	int i, j, degree_sum = 0;

	n = r * c;
	printf("Board size: %d x %d = %d vertices\n", r, c, n);
	
	matrix = generate_matrix_int(n, n);
	if (!matrix)
		return ;
	set_board_knight(matrix, r, c);		// -> board_init.c
	
	// Calculate vertex degrees
	printf("Vertex degrees: ");
	for (i = 0; i < n; i++) {
		int degree = 0;
		for (j = 0; j < n; j++) {
			if (matrix[i][j] == 1) degree++;
		}
		printf("%d ", degree);
		degree_sum += degree;
	}
	printf("\nTotal edges: %d, Average degree: %.2f\n", degree_sum / 2, (double)degree_sum / n);
	
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
