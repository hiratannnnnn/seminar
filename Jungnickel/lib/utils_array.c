#include "lib.h"

int		max_of_array(int *arr, int n)
{
	int max, i;
	max = arr[0];

	for (i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

int		min_of_array(int *arr, int n)
{
	int min, i;
	min = arr[0];

	for (i = 1; i < n; i++)
		if (arr[i] < min)
			min = arr[i];
	return min;
}
