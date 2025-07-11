#include "lib.h"


Vertex	*create_vertex(int id)
{
	Vertex	*vertex;

	vertex = (Vertex *)xmalloc(sizeof(Vertex));
	if (!vertex)
		return (NULL);
	vertex->id = id;
	vertex->label = id;
	vertex->incidence = NULL;
	return (vertex);
}

Vertex	**create_vertex_array(int n)
{
	int		i;
	Vertex	**vs;

	vs = (Vertex **)xmalloc(sizeof(Vertex *) * n);
	if (!vs)
		return (NULL);
	i = 0;
	while (i < n)
	{
		vs[i] = create_vertex(i);
		if (!vs[i])
		{
			free_vertex_array(vs, i);
			return (NULL);
		}
		i++;
	}
	return (vs);
}

void reset_labels(Vertex **vs, int n)
{
	int i;

	for (i = 0; i < n; i++)
		vs[i]->label = i;
}

void	update_labels(PathNode *node, int label)
{
	while (node)
	{
		node->v->label = label;
		node = node->next;
	}
}
