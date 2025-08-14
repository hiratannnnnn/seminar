#include "mintree.h"

int is_in_Vi(PathNode *node, int index)
{
	PathNode *cur;

	cur = node;
	while (cur)
	{
		// printf("[DEBUG] searching for %d\n", index);
		if (cur->v->id == index)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int is_in_Vi_label(PathNode *node, int index)
{
	PathNode *cur;

	cur = node;
	while (cur)
	{
		if (cur->v->label == index)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void free_pathnode_array(PathNode **ps, int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (ps[i])
			free_pathnode(&ps[i]);
	xfree(ps, sizeof(PathNode *) * n);
}
