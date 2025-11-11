#include "genome.h"

void	free_component(Component *comp)
{
	xfree(comp, sizeof(Component));
}

void	free_component_list(Component *head)
{
	Component *cur, *tmp;

	cur = head;
	while (cur)
	{
		tmp = cur->next;
		free_component(cur);
		cur = tmp;
	}
}

Component *create_component(void)
{
	Component *comp;

	comp = (Component *)xmalloc(sizeof(Component) * 1);
	if (!comp)
		return (NULL);
	comp->start = NULL;
	comp->end = NULL;
	comp->type = 0;
	comp->oriented = 0;
	comp->prev = NULL;
	comp->next = NULL;
	return (comp);
}
