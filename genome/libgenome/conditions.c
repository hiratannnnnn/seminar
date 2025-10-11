#include "libgenome.h"

/**
 * 0, 1, 2, 3, 4, 5
 * from 1 to 4 is valid
 */
int can_rev(int x, int y, int size)
{
	if (x < 1)
		return (0);
	if (y <= x)
		return (0);
	if (size - 1 < y)
		return (0);
	return (1);
}

int can_revrev(int x, int y, int z, int size)
{
	if (x < 1)
		return (0);
	if (y <= x)
		return (0);
	if (z <= y)
		return (0);
	if (size - 1 < y)
		return (0);
	return (1);
}

int can_transpose(int x, int y, int z, int size)
{
	if (x < 1)
		return (0);
	if (y <= x)
		return (0);
	if (z <= y)
		return (0);
	if (size - 1 < z)
		return (0);
	return (1);
}

int can_block_interchange(int x, int y, int z, int w, int size)
{
	if (x < 1)
		return (0);
	if (y <= x)
		return (0);
	if (z < y)
		return (0);
	if (w <= z)
		return (0);
	if (size - 1 < w)
		return (0);
	return (1);
}
