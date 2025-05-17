#ifndef JUNG_H
# define JUNG_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
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



// generate_matrix.c
int				**generate_matrix(int r, int c);




// generate_random_adj.c
void 			generate_random_adj(int n, double edge_prob, char const *filename);

// generate_random_euler.c
int 			**generate_random_euler(int n);

// generate_random_tree.c
int				*generate_random_prufer(int n);
int 			*count_degrees_from(const int *prufer, int n);
int 			**generate_random_tree(int n);


// is_tree.c
int				is_tree(int **matrix, int n);

// read_adj.c
int 			**read_adj(int *n, char const *filename);

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

// utils_print.c
void 			print_matrix(int **matrix, int r, int c);
void			print_array_int(int *arr, int n);
int				write_to_file(int **matrix, int n, char const *filename);

// utils.c
void			ft_putnbr(long n);
void			ft_putstr(char const *str);

// utils_lists.c
Node			*create_node(int edge_id);
void			append_node(Node **head, Node *new_node);
void			insert_node_after(Node *pos, Node *new_node);
Node 			*get_last_node(Node *head);

#endif
