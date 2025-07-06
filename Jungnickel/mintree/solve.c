#include "mintree.h"

void	solve(Vertex **vs, EdgeNode **head, int n)
{
	PathNode **ps;
	EdgeNode **es;
	int i;
	int k;

	ps = (PathNode **)xmalloc(sizeof(PathNode *) * n);
	es = (EdgeNode **)xmalloc(sizeof(EdgeNode *) * n);
	for (i = 0; i < n; i++)
	{
		ps[i] = create_pathnode(vs[i]);
		es[i] = NULL;
	}

	for (k = 0; k < n - 1; k++)
	{
		
	}
}
