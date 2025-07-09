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

int cmp_double_desc(double a, double b)
{
	if (b - a > 0)
		return 1;
	return 0;
}

int cmp_double_asc(double a, double b)
{
	if (a - b > 0)
		return 1;
	return 0;
}

int cmp_double_bogo(double a, double b)
{
	a = a - b;
	return (1 - 2 * (rand() % 2));
}
