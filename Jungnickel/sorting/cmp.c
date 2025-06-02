#include "sorting.h"

// if cmp > 0, swap.
// descending order
int cmp_bigger(int a, int b)
{
	return (b - a);
}

// ascending order
int cmp_smaller(int a, int b)
{
	return (a - b);
}
