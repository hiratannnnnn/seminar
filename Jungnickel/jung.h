#ifndef JUNG_H
# define JUNG_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct Edge
{
	int			id;
	int			from;
	int			to;
	int			used;
	struct Edge	*next;
}				Edge;

typedef struct Vertex
{
	int			id;
	Edge		*incidence;
}				Vertex;

typedef struct Node
{
	int			edge_id;
	struct Node	*prev;
	struct Node	*next;
}				Node;

int				*count_degrees(int *prufer, int n);

// generate_matrix.c
int				**generate_matrix(int r, int c);

int				*generate_prufer_code(int *degrees, int n);
int				**generate_matrix_from_degree(int *degs, int n);
void			draw_graph(int **matrix, int n);
int				is_tree(int **matrix, int n);
int				find_min_vertex(int *degs, int n);
int				find_max_vertex(int *degs, int n, int exclude);
int				find_min(int *prufer, int *appeared, int vertices, int n,
					int current_index);

// algo_EULER.c
void			algo_euler(Vertex **vs, int n, int s, Node **K);

// utils_edges.c
Edge			*create_edge(int id, int from, int to);
Vertex			*create_vertex(int id);
Vertex			**create_vertex_array(int n);
void			add_edge(Vertex **vs, int from, int to, int edge_id);
void			print_vertex(const Vertex *v);
void			print_vertices(const Vertex **vs, int n);
void			print_edge_list(Edge *head);

// utils_free.c
void			free_array_int(int **arr, const int r);
void			free_edge_list(Edge *head);
void			free_node_list(Node *head);
void			free_vertex(Vertex *vertex);
void			free_vertex_array(Vertex **vs, int n);

// utils.c
void			ft_putnbr(long n);
void			ft_putstr(char const *str);

// utils_lists.c
Node			*create_node(int edge_id);
void			append_node(Node **head, Node *new_node);
void			insert_node_after(Node *pos, Node *new_node);
void			free_node_list(Node *head);

#endif
