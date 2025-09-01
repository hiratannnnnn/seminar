#include "lib.h"

void	ft_putnbr(long n)
{
	long long	num;
	char		c;

	num = (long long)n;
	if (num < 0)
	{
		num = -num;
		write(1, "-", 1);
	}
	if (num >= 10)
		ft_putnbr(num / 10);
	c = num % 10 + '0';
	write(1, &c, 1);
}

void	ft_putstr(char const *str)
{
	while (*str)
		write(1, str++, 1);
}

int		sum_matrix(int **matrix, int r, int c)
{
	int sum;
	int i;

	sum = 0;
	for (i = 0; i < r; i++)
		sum += sum_array(matrix[i], c);
	return sum;
}

int 	sum_array(int *arr, int n)
{
	int sum;
	int j;

	sum = 0;
	for (j = 0; j < n; j++)
		sum += arr[j];
	return sum;
}

int		min_int(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

int 	max_int(int a, int b)
{
	if (a < b)
		return b;
	return a;
}

double	min_double(double a, double b)
{
	if (fabs(a - b) < DBL_EPSILON)
		return a;
	if (a < b)
		return a;
	return b;
}

double 	max_double(double a, double b)
{
	if (fabs(a - b) < DBL_EPSILON)
		return a;
	if (a < b)
		return b;
	return a;
}
