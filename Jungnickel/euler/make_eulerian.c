#include "euler.h"

static int     need_double_edge(int *degree, int n)
{
    int i;
    if (n % 2 == 1)
        return (0);
    for (i = 0; i < n; i++)
    {
        if (degree[i] == n - 1)
			return (1);
    }
	return (0);
}

static void	backtrack_euler(Vertex **vs, int from, int n, PathNode **head)
{

}

int		make_eulerian(int **matrix, int n)
{
    int *degree;
    int *visited;
    degree = xmalloc(sizeof(int) * n);
    visited = xcalloc(n, sizeof(int));
    if (!degree)
        return -1;
    compute_degrees(matrix, n, degree);
	if (need_double_edge(degree, n))
		return 0;

    Vertex **vs;
    Edge *edge;
    PathNode *head;

    vs = compliment_adj_list(matrix, n, 1);
    int i;
    for (i = 0; i < n; i++)
    {
        if (degree[i] % 2 == 0) continue;
        edge = vs[i]->incidence;
        while (edge)
        {
            backtrack_euler(vs, i, n, &head);
            add_path(matrix, head);
            
            edge = edge->next;
        }
    }
}