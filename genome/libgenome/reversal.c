#include "libgenome.h"

/**
 * including @param x, @param y
 *
 * 1, 2, 3, 4, 5
 * ↓ rev(1, 3) ↓
 * 1, -4, -3, -2, 5
 */
void	rev(int *perm, int x, int y, int n)
{
	int left, right, tmp;

	if (!can_rev(x, y, n))
		return ;
	left = x;
	right = y - 1;
	while (left <= right)
	{
		tmp = (-1) * perm[left];
		perm[left] = (-1) * perm[right];
		perm[right] = tmp;

		left++; right--;
	}
}


void	revrev(int *perm, int x, int y, int z, int n)
{
	if (!can_revrev(x, y, z, n))
		return ;
	rev(perm, x, y, n);
	rev(perm, y, z, n);
}
