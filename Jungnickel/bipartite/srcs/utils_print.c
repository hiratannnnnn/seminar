#include "bipartite.h"

void print_array_int(int *arr, int const c)
{
	int j;

	for (j = 0; j < c; j++)
		printf("%d%c", arr[j], j == c - 1 ? '\n' : ' ');
}

void print_matrix_int(int **matrix, int const r, int const c)
{
	int i;

	for (i = 0; i < r; i++)
		print_array_int(matrix[i], c);
}

void 	print_array_double(double *arr, int c)
{
	int j;

	for (j = 0; j < c; j++)
		printf("%.6f%c", arr[j], j == c - 1 ? '\n' : ' ');
}

void	print_matrix_double(double **matrix, int r, int c)
{
	int i;

	for (i = 0; i < r; i++)
		print_array_double(matrix[i], c);
}

void	print_info()
{
	double used_time;

	used_time = ((double) (proc_end - proc_start)) / CLOCKS_PER_SEC;
	printf("mem_peak: %d\n", (int)mem_peak);
	printf("remaining mem: %d\n", (int)mem);
	printf("proccess time: %f\n", used_time);
}
