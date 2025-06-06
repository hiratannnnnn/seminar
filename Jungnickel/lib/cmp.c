#include "lib.h"

// if cmp > 0, swap.
// descending order
int cmp_int_desc(int a, int b)
{
	return (b - a);
}

// ascending order
int cmp_int_asc(int a, int b)
{
	return (a - b);
}

// sort randomly
int cmp_int_bogo(int a, int b)
{
	return (1 - 2 * ((rand() * (a + b)) % 2));
}
