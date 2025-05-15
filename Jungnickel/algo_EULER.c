#include "jung.h"

static void	trace(Vertex **vs, int v, int *new_edge, Node **C, int **e_pos,
		int *used, int *used_list, int *used_list_size, int n)
{
	Edge	*edge;
	Node	*node;

	while (1)
	{
		edge = vs[v]->incidence;
		while (edge && !new_edge[edge->id])
			edge = edge->next;
		if (!edge)
			return ;
		new_edge[edge->id] = 0;
		node = create_node(edge->id);
		append_node(C, node);
		if ((*e_pos)[v] == -1)
			(*e_pos)[v] = node->edge_id;
		v = edge->to;
		if (!used[v])
		{
			used[v] = 1;
			used_list[(*used_list_size)++] = v;
		}
	}
}

static void	insert_C_in_K(Node **K, Node *C, int insert_edge_id)
{
	Node	*cur;
	Node	*prev;
	Node	*last;

	if (!C)
		return ;
	cur = *K;
	while (cur && cur->edge_id != insert_edge_id)
		cur = cur->next;
	if (!cur)
	{
		append_node(K, C);
		return ;
	}
	prev = cur->prev;
	if (prev)
		prev->next = C;
	last = C;
	while (last->next)
		last = last->next;
	last->next = cur;
	cur->prev = last;
	if (cur == *K)
		*K = C;
}

void	algo_euler(Vertex **vs, int n, int s, Node **K)
{
	int		*used;
	int		*new_edge;
	int		*used_list;
	int		used_list_size;
	int		*e_pos;
	int		i;
	Edge	*e;
	int		u;
	Node	*C;

	used = (int *)calloc(n, sizeof(int));
	new_edge = (int *)calloc(n * n, sizeof(int));
	used_list = (int *)malloc(sizeof(int) * n);
	used_list_size = 0;
	e_pos = (int *)malloc(sizeof(int) * n);
	i = 0;
	while (i < n)
	{
		used[i] = 0;
		e_pos[i] = -1;
		i++;
	}
	i = 0;
	while (i < n)
	{
		e = vs[i]->incidence;
		while (e)
		{
			new_edge[e->id] = 1;
			e = e->next;
		}
		i++;
	}
	used[s] = 1;
	used_list[used_list_size++] = s;
	trace(vs, s, new_edge, K, &e_pos, used, used_list, &used_list_size, n);
	while (used_list_size > 0)
	{
		u = used_list[--used_list_size];
		C = NULL;
		trace(vs, u, new_edge, &C, &e_pos, used, used_list, &used_list_size, n);
		insert_C_in_K(K, C, e_pos[u]);
	}
	free(used);
	free(new_edge);
	free(used_list);
	free(e_pos);
}
