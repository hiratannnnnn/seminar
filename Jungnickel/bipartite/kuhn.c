#include "bipartite.h"

static int bpm(int u, int **matrix, int *match_to, int *visited, int a, int b)
{
	int v;

	for (v = 0; v < b; v++)
	{
		if (matrix[u][a+v] && !visited[v])
		{
			printf("[DEBUG] %d %d, going to match_to[%d]: %d\n", u, v, v, match_to[v]);
			visited[v] = 1;
			if (match_to[v] == -1 || bpm(match_to[v], matrix, match_to, visited, a, b))
			{
				printf("[DEBUG] set match_to[%d]: %d\n", v, u);
				match_to[v] = u;
				print_array_int(match_to, b);
				return (1);
			}
		}
	}
	return (0);
}

int max_bipartite_matching(int **matrix, int a, int b, int *match_to)
{
	int result;
	int u, v;
	int *visited;

	result = 0;
	for (v = 0; v < b; v++)
		match_to[v] = -1;
	for (u = 0; u < a; u++)
	{
		printf("[DEBUG] watching %d\n", u);
		visited = (int *)xcalloc(b, sizeof(int));
		if (!visited)
			return (-1);
		if (bpm(u, matrix, match_to, visited, a, b))
		{
			// print_array_int(match_to, b);
			result++;
		}
		free_array_int(visited, b);
	}
	return result;
}
