#include "../jung.h"

int	**generate_adj(int r, int c)
{
	int	**result;
	int	i;
	int	j;

	result = (int **)malloc(sizeof(int *) * r);
	i = 0;
	while (i < r)
	{
		result[i] = (int *)malloc(sizeof(int) * c);
		j = 0;
		while (j < c)
		{
			result[i][j] = 0;
			j++;
		}
		i++;
	}
	return (result);
}
