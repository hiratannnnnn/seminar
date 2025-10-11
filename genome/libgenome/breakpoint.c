#include "libgenome.h"

int count_breakpoints(int *perm, int n)
{
	int count, diff, i;

	count = 0;
	for (i = 0; i < n - 1; i++)
	{
		diff = abs(perm[i+1]) - abs(perm[i]);
		if (diff != 1)
			count++;
	}
	return (count);
}
