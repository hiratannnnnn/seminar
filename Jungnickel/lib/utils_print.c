#include "lib.h"

void print_matrix(int **matrix, int r, int c)
{
	if (!matrix)
	{
		printf("matrix is NULL\n");
		return;
	}

	int i;
	for (i = 0; i < r; i++)
	{
		if (!matrix[i])
			return;
		print_array_int(matrix[i], c);
	}
}

void print_array_int(int *arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d", arr[i]);
		printf((i == n - 1) ? "\n" : " ");
	}
}
