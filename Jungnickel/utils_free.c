#include "jung.h"

void	free_array_int(int **arr, const int r)
{
	int	i;

	i = 0;
	while (i < r)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
