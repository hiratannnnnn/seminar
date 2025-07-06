#include "lib.h"

Edge	*create_edge(int id, int from, int to)
{
	Edge	*edge;

	edge = (Edge *)xmalloc(sizeof(Edge));
	if (!edge)
		return (NULL);
	edge->id = id;
	edge->from = from; // id of vertice;
	edge->to = to;
	edge->cost = 0.0;
	edge->next = NULL;
	return (edge);
}

int 	len_edge_list(Edge *head)
{
	int count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return count;
}


void	add_directed_edge(Vertex **vs, int from, int to, int edge_id)
{
	Edge *edge = create_edge(edge_id, from, to);
	if (!edge)
		return;
	edge->next = vs[from]->incidence;
	vs[from]->incidence = edge;
}

void	add_undirected_edge(Vertex **vs, int from, int to, int edge_id)
{
	add_directed_edge(vs, from, to, edge_id);
	add_directed_edge(vs, to, from, edge_id);
}
