#include "perms.h"

int		*gen_perm(int start, int end, int *n)
{
	int *perm;
	int i;

	*n = end - start + 1;
	if (*n < 1)
		return (NULL);
	perm = xmalloc(sizeof(int) * (*n));
	if (!perm)
		return (NULL);

	for (i = 0; i < *n; i++)
		perm[i] = start + i;
	shuffle_perm(perm, *n);
	return perm;
}

int 	*gen_unsigned_perm(int n)
{
	int *perm;
	int i;

	perm = xmalloc(sizeof(int) * n);
	if (!perm)
		return (NULL);

	for (i = 1; i <= n; i++)
		perm[i-1] = i;
	shuffle_perm(perm, n);
	return (perm);
}

int		*gen_signed_perm(int n)
{
	int *perm;
	int i;

	perm = gen_unsigned_perm(n);
	if (!perm)
		return (NULL);
	for (i = 0; i < n; i++)
		if (rand() % 2 == 0)
			perm[i] = (-1) * perm[i];
	return (perm);
}

int 	*gen_id_perm(int n)
{
	int *perm;
	int i;

	perm = (int *)xmalloc(sizeof(int) * n);
	if (!perm)
		return (NULL);
	for (i = 0; i < n; i++)
		perm[i] = i + 1;
	return (perm);
}

void	*add_extremity(int *perm, int *n)
{
	int *new_perm;
	int i;

	new_perm = xrealloc(perm, (*n) * sizeof(int), (*n + 2) * sizeof(int));
	if (!new_perm)
		return NULL;

	for (i = *n; i > 0; i--)
		new_perm[i] = new_perm[i - 1];
	new_perm[0] = 0;
	new_perm[*n+1] = *n+1;
	*n = *n + 2;
	return (new_perm);
}

void	*add_pairs(int *perm, int *n)
{
	int *new_perm;
	int new_size;
	int i;

	if (*n < 2 || perm[0] != 0 || perm[*n-1] != *n-1)
		return (printf("extremities are wrong.\n"), perm);
	new_size = (*n - 2) * 2 + 2;
	new_perm = xrealloc(perm, (*n) * sizeof(int), new_size * sizeof(int));
	if (!new_perm)
		return (NULL);
	new_perm[new_size-1] = new_perm[*n-1];
	for (i = *n-2; i > 0; i--)
	{
		new_perm[i * 2] = new_perm[i];
		new_perm[i * 2 - 1] = new_perm[i] * (-1);
	}
	new_perm[0] = 0;
	*n = new_size;
	return (new_perm);
}
