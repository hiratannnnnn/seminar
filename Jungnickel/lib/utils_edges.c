#include "lib.h"

Edge	*create_edge(int id, int from, int to)
{
	Edge	*edge;

	edge = (Edge *)malloc(sizeof(Edge));
	if (!edge)
		return (NULL);
	edge->id = id;
	edge->from = from; // id of vertice;
	edge->to = to;
	edge->used = 0;
	edge->next = NULL;
	return (edge);
}

Vertex	*create_vertex(int id)
{
	Vertex	*vertex;

	vertex = (Vertex *)malloc(sizeof(Vertex));
	if (!vertex)
		return (NULL);
	vertex->id = id;
	vertex->incidence = NULL;
	return (vertex);
}

Vertex	**create_vertex_array(int n)
{
	int		i;
	Vertex	**vs;

	vs = (Vertex **)malloc(sizeof(Vertex *) * n);
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
	add_directed_edge(vs, to, from ,edge_id);
}
