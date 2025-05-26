#include "lib.h"

/**
 * @brief generates n length permutation randomly
 * 0, 1, ..., n - 1
 * @param n size of array
 */

int		*random_perm(int n)
{
	int *perm;
	int i, j, tmp;

	perm = xmalloc(sizeof(int) * n);
	if (!perm)
		return (NULL);
	for (i = 0; i < n; i++)
		perm[i] = i;
	for (i = n - 1; i > 0; i--)				// Fisher-Yates Shuffle
	{
		j = rand() % (i + 1);
		tmp = perm[i];
		perm[i] = perm[j];
		perm[j] = tmp;
	}
	return perm;
}
