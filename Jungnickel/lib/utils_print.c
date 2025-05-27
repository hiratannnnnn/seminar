#include "lib.h"

void print_matrix(int **matrix, int r, int c)
{
	if (!matrix)
	{
		printf("matrix is NULL\n");
		return;
	}

	int i;
	for (i = 0; i < r; i++)
	{
		if (!matrix[i])
			return;
		print_array_int(matrix[i], c);
	}
}

void print_array_int(int *arr, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d", arr[i]);
		printf((i == n - 1) ? "\n" : " ");
	}
}


void	print_vertex(Vertex *v)
{
	if (!v)
		return ;
	ft_putstr("vId: ");
	ft_putnbr(v->id);
	print_edge_list(v->incidence);
	ft_putstr("\n");
}

void	print_vertices(Vertex **vs, int n)
{
	int	i;

	i = 0;
	if (!vs)
		return ;
	while (i < n)
	{
		print_vertex(vs[i]);
		i++;
	}
}

void	print_edge_list(Edge *head)
{
	Edge	*cur;

	cur = head;
	while (cur)
	{
		printf(" -> ");
		printf("%d", cur->to);
		cur = cur->next;
	}
}

void 	print_path_node(PathNode *head)
{
	PathNode	*cur;

	cur = head;
	while (cur)
	{
		printf(" -> ");
		printf("%d", cur->v->id);
		cur = cur->next;
	}
}

void	print_array_char(char **ss, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%s\n", ss[i]);
	}
}

void	print_mem_peak()
{
	printf("mem_peak: %d\n", (int)mem_peak);
	printf("remaining mem: %d\n", (int)mem);
}
