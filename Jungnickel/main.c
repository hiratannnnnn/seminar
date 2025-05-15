#include "jung.h"

void	print_euler_tour(Node *K)
{
	Node	*cur;

	cur = K;
	ft_putstr("Euler tour (edge ids): ");
	while (cur)
	{
		ft_putnbr(cur->edge_id);
		ft_putstr(" ");
		cur = cur->next;
	}
	ft_putstr("\n");
}

int	main(void)
{
	int		n;
	Vertex	**vs;
	Node	*K;

	n = 5;
	K = NULL;
	vs = create_vertex_array(n);
	add_edge(vs, 0, 1, 0);
	add_edge(vs, 1, 2, 1);
	add_edge(vs, 2, 3, 2);
	add_edge(vs, 4, 0, 3);
	add_edge(vs, 1, 3, 4);
	add_edge(vs, 1, 4, 5);
	print_vertices((const Vertex **)vs, n);
	algo_euler(vs, n, 0, &K);
	print_euler_tour(K);
	free_node_list(K);
	free_vertex_array(vs, n);
	return (0);
}
