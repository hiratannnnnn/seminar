#include "libgenome.h"

/**
 * 1 <= x < y < z <= n-1
 * 1, 2, 3, 4, 5, 6, 7
 * transpose(1, 3, 5)
 * 1, 4, 5, 2, 3, 6, 7
 */
void	transpose(int *perm, int x, int y, int z, int n)
{
	int former, latter;

	if (!can_transpose(x, y, z, n))
	{
		printf("cannot transpose.\n");
		return ;
	}
	former = y - x;
	latter = z - y;
	rev(perm, x, z, n);
	rev(perm, x + latter, y + latter, n);
	rev(perm, y - former, z - former, n);
}

/**
 * 1 <= x < y <= z < w <= n - 1
 * 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
 * block_interchange(1, 4, 5, 7)
 * 0, 5, 6, 4, 1, 2, 3, 7, 8, 9
 */
void	block_interchange(int *perm, int x, int y, int z, int w, int n)
{
	int former, inner, latter;
	if (!can_block_interchange(x, y, z, w, n))
	{
		printf("cannot block-interchange.\n");
		return ;
	}
	former = y - x;
	inner = z - y;
	latter = w - z;
	rev(perm, x, w, n);
	rev(perm, x + inner + latter, y + inner + latter, n);
	rev(perm, z - former - inner, w - former - inner, n);
	rev(perm, w - former - inner, x + inner + latter, n);
}
