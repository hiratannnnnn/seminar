#include "../jung.h"

void print_matrix(int **matrix, int r, int c)
{
	int i, j;
	for (i = 0; i < r; i++)
		print_array_int(matrix[i], c);
	ft_putstr("size=( ");
	ft_putnbr(r);
	ft_putstr(", ");
	ft_putnbr(c);
	ft_putstr(" ).");
}

void print_array_int(int *arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		ft_putnbr(arr[i]);
		ft_putstr((i == n - 1) ? "\n" : " ");
	}
}
