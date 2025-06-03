// filepath: /c/Users/PC_User/seminar/Jungnickel/tsp/main.c
#include "tsp.h"

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
	int *best_path;
	int n;

	n = 13;
	matrix = generate_weighted_matrix(n, 30);
	if (!matrix)
		return (1);
	print_matrix(matrix, n, n);
	best_path = (int *)xcalloc(n, sizeof(int));
	if (!best_path)
	{
		free_matrix_int(matrix, n, n);
		return (1);
	}
	printf("%d\n", tsp_bruteforce(matrix, n, best_path));
	printf("%d\n", tsp_greedy(matrix, n, best_path));
	// free
	free_matrix_int(matrix, n, n);
	free_array_int(best_path, n);
	proc_end = clock();
	print_info();
	return (0);
}
