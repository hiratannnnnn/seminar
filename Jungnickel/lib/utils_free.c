#include "lib.h"

void	free_edge_list(Edge *head)
{
	Edge	*cur;
	Edge	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	free_node_list(Node *head)
{
	Node	*cur;
	Node	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	free_vertex(Vertex *vertex)
{
	if (!vertex)
		return ;
	free_edge_list(vertex->incidence);
	free(vertex);
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
	free(vs);
}
