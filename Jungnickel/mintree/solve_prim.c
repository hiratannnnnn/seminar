#include "mintree.h"

void	solve_prim(Vertex **vs, int n)
{
	printf("%d%d", vs[0]->id, n);
	// double *g;
	// PathNode *S;
	// EdgeNode *T;
	// int i, j;
	// Min_V min;

	// g = (double *)xmalloc(sizeof(double) * n);
	// S = NULL;
	// T = NULL;
	// g[0] = 0.0;
	// for (i = 1; i < n; i++)
	// 	g[i] = DBL_MAX;
	// while (count_pathnodes(S) < n)
	// {
	// 	printf("[DEBUG] current S is %d length\n", (int)count_pathnodes(S));
	// 	min.min_cost = DBL_MAX;
	// 	min.v = NULL;
	// 	for (i = 0; i < n; i++)
	// 	{
	// 		if (!is_in_Vi(S, i) && g[i] < min.min_cost)
	// 		{
	// 			printf("[DEBUG] update min to %d which g[i] is %f\n", i, g[i]);
	// 			min.min_cost = g[i];
	// 			min.v = vs[i];
	// 		}
	// 	}
	// 	printf("[DEBUG] merge S and %d\n", min.v->id);
	// }
}
