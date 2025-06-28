#include "tsp.h"

static int calc_path_cost(int **matrix, int *path, int n)
{
	int cost;
	int i;

	cost = 0;
	for (i = 0; i < n - 1; i++)
	{
		if (matrix[path[i]][path[i+1]] < 0)
			return INT_MAX;
		cost += matrix[path[i]][path[i+1]];
	}
	if (matrix[path[n-1]][path[0]] < 0)
		return INT_MAX;
	cost += matrix[path[n-1]][path[0]];
	return cost;
}

/**
 * @brief known as a algorithm for generating permutation in a dictionary order.
 * Narayana Pandita's algorithm
 */
static int next_permutation(int *a, int n)
{
	int i, j, k, l, tmp;

	i = n - 2;
	while (i >= 0 && a[i] >= a[i+1])
		i--;
	if (i < 0)
		return (0);
	j = n - 1;
	while (a[j] <= a[i])
		j--;
	tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
	k = i + 1;
	l = n - 1;
	while (k < l)
	{
		tmp = a[k];
		a[k] = a[l];
		a[l] = tmp;
		k++;
		l--;
	}
	return (1);
}

int		tsp_bruteforce(int **matrix, int n, int *best_path)
{
	int *perm;
	int min_cost, cost, i;

	perm = xmalloc(sizeof(int) * n);
	if (!perm)
		return -1;
	for (i = 0; i < n; i++)
		perm[i] = i;
	min_cost = INT_MAX;
	do
	{
		cost = calc_path_cost(matrix, perm, n);
		if (cost < min_cost)
		{
			min_cost = cost;
			printf("%d: ", min_cost);
			print_array_int(perm, n, 2);
			memcpy(best_path, perm, sizeof(int) * n);
		}
	} while (next_permutation(perm + 1, n - 1));
	free_array_int(perm, n);
	return min_cost;
}

// int		tsp_held_karp(int **matrix, int n, int *best_path)
// {

// }

static int		tsp_greedy_each(int **matrix, int n, int *path, int offset)
{
	int *used;
	int cost, last, min_w, min_j;
	int i, j;

	used = (int *)xcalloc(n, sizeof(int));
	if (!used)
		return (-1);
	cost = 0;
	path[0] = offset;
	used[offset] = 1;
	for (i = 1; i < n; i++)
	{
		last = path[i - 1];
		min_w = INT_MAX;
		min_j = -1;
		for (j = 0; j < n; j++)
		{
			if (!used[j] && matrix[last][j] > 0 &&
				matrix[last][j] < min_w)
			{
				min_w = matrix[last][j];
				min_j = j;
			}
		}
		if (min_j == -1)
			return (free_array_int(used, n), INT_MAX);
		path[i] = min_j;
		used[min_j] = 1;
		cost += min_w;
	}
	if (matrix[path[n-1]][offset] < 0)
		return (free_array_int(used, n), INT_MAX);
	cost += matrix[path[n-1]][offset];
	return (free_array_int(used, n), cost);
}

int tsp_greedy(int **matrix, int n, int *best_path)
{
	int min_cost, offset, cost;
	int *tmp_path;

	min_cost = INT_MAX;
	tmp_path = (int *)xcalloc(n, sizeof(int));
	if (!tmp_path)
		return -2;
	for (offset = 0; offset < n; offset++)
	{
		cost = tsp_greedy_each(matrix, n, tmp_path, offset);
		if (cost < min_cost)
		{
			min_cost = cost;
			memcpy(best_path, tmp_path, sizeof(int) * n);
		}
	}
	free_array_int(tmp_path, n);
	return min_cost;
}
