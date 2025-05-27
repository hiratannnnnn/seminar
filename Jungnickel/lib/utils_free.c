#include "lib.h"

void	free_edge_list(Edge *head)
{
	Edge	*cur;
	Edge	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		xfree(cur, sizeof(Edge));
		cur = next;
	}
}

void	free_vertex(Vertex *vertex)
{
	if (!vertex)
		return ;
	free_edge_list(vertex->incidence);
	xfree(vertex, sizeof(Vertex));
}

void	free_vertex_array(Vertex **vs, int n)
{
	int	i;

	if (!vs)
		return ;
	i = 0;
	while (i < n)
	{
		free_vertex(vs[i]);
		i++;
	}
	xfree(vs, sizeof(Vertex *) * n);
}
