#include "lib.h"

void print_matrix_int(int **matrix, int r, int c)
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

void	print_matrix_double(double **matrix, int r, int c)
{
	int i;

	for (i = 0; i < r; i++)
		print_array_double(matrix[i], c);
}

void 	print_array_double(double *arr, int c)
{
	int j;

	for (j = 0; j < c; j++)
		printf("%.6f%c", arr[j], j == c - 1 ? '\n' : ' ');
}

void	print_vertex(Vertex *v)
{
	if (!v)
		return ;
	printf("vId: %d", v->id);
	print_edge_list(v->incidence);
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
	printf("\n");
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
	printf("\n");
}

void	print_array_char(char **ss, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%s\n", ss[i]);
	}
}

void	print_info()
{
	double used_time;

	used_time = ((double) (proc_end - proc_start)) / CLOCKS_PER_SEC;
	printf("mem_peak: %d\n", (int)mem_peak);
	printf("remaining mem: %d\n", (int)mem);
	printf("proccess time: %f\n", used_time);
}
