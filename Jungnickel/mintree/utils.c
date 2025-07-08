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
