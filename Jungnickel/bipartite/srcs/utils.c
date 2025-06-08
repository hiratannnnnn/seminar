#include "bipartite.h"

int	print_hungarian_check(double **matrix, int *match_to, int n, int indent)
{
	int i;
	int count;

	count = 0;
	for (i = 0; i < n; i++)
	{
		if (match_to[i] > -1)
		{
			printf("%.4f%c", matrix[match_to[i]][i], (count % indent == indent - 1) ? '\n' : ' ');
			count++;
		}
	}
	return count;
}
