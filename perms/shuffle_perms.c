#include "perms.h"

void shuffle_perm(int *perm, int n)
{
	int i, j, tmp;

	// Fisher-Yates Shuffle
	for (i = n - 1; i > 0; i--)
	{
		j = rand() % (i + 1);
		tmp = perm[i];
		perm[i] = perm[j];
		perm[j] = tmp;
	}
}
