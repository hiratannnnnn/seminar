
#include "genome.h"

void	free_ext(Extremity *ext)
{
	xfree(ext, sizeof(Extremity));
}

void 	free_array_exts(Extremity **exts, int n)
{
	int i;

	i = 0;
	while (i < n * 2)
	{
		if (exts[i])
			free_ext(exts[i]);
		i++;
	}
	xfree(exts, sizeof(Extremity *) * (n * 2));
}

Extremity *create_ext(int id, int sign)
{
	Extremity *ext;

	ext = (Extremity *)xmalloc(sizeof(Extremity) * 1);
	if (!ext)
		return (NULL);
	ext->id = id;
	ext->sign = sign;
	ext->reality = NULL;
	ext->desire = NULL;
	return (ext);
}

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
		tmp = cur;
		free_component(cur);
		cur = tmp->next;
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

int is_all_true(int *array, int n)
{
	int i;

	for (i = 0; i < n; i++)
		if (array[i] == 0)
			return (0);
	return (1);
}

Extremity *get_pair_of(Extremity_ctx *ctx, Extremity *ext)
{
	if (ext->sign == 1)
		return (ctx->exts[2 * (ext->id - 1)]);
	else
		return (ctx->exts[2 * (ext->id - 1) + 1]);
}
