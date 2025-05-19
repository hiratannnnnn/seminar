#ifndef JUNG_H
# define JUNG_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

/* ========= Data Structure =========*/

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

typedef struct PathNode
{
    int			vertex;
    struct PathNode *next;
}				PathNode;

/* ========= Matrix Operations =========*/

// matrix_operations.c
int				**generate_matrix(int r, int c);
void			free_array_int(int **arr, const int r);
int				write_to_file(int **matrix, int n, char const *filename);

/* ========= Graph Generation =========*/

// random_adj.c
void 			generate_random_graph(int n, double edge_prob, char const *filename);

// random_tree.c
int				*generate_random_prufer(int n);
int 			*count_degrees_from(const int *prufer, int n);
int 			**generate_random_tree(int n);
void            build_tree_from(int **matrix, int *prufer, int *degree, int n);

// euler_graph.c
int 			**generate_random_euler(int n);
int             make_eulerian(int **matrix, int n);

/* ========= Graph Analysis =========*/

// graph_analysis.c
int				is_tree(int **matrix, int n);
void            compute_degrees(int **matrix, int n, int *degree);
int             find_odd_vertices(int *degree, int n, int *odd_list);

/* ========= Path Finding =========*/

// path_operations.c
// int             find_path_dfs(int **matrix, int n, int current, int end, int *visited, int state);
PathNode        *find_path_dfs(int **matrix, int n, int current, int end, int *visited, PathNode *path);
PathNode        *find_cycle_dfs(int **matrix, int n, int start, int current, int *visited, int depth);
void            add_edges_along_path(int **matrix, PathNode *path);
void            free_path(PathNode *path);

// graph_connections.c
int             make_trail(int **matrix, int n, int v1, int v2);
int             make_cycle(int **matrix, int n, int v);
int             find_common_vertex(int **matrix, int n, int v1, int v2);
int             pair_odd_vertices(int **matrix, int n, int *odd_list, int odd_count);

/* ========= Graph Format Conversion =========*/

// graph_conversion.c
Vertex          **adj_matrix_to_vertices(int **matrix, int n);
int             **vertices_to_adj_matrix(Vertex **vertices, int n);

/* ========= Input Processing =========*/

// read_adj.c
int 			**read_adj(int *n, char const *filename);

/* ========= Algorithms =========*/

// algo_euler.c
void			algo_euler(Vertex **vs, int n, int s, Node **K);

/* ========= Utilities =========*/

// utils_edges.c
Edge			*create_edge(int id, int from, int to);
Vertex			*create_vertex(int id);
Vertex			**create_vertex_array(int n);
void			add_edge(Vertex **vs, int from, int to, int edge_id);
void			print_vertex(const Vertex *v);
void			print_vertices(const Vertex **vs, int n);
void			print_edge_list(Edge *head);

/* ========= Euler Tour Utilities =========*/

// utils_basic.c
void			ft_putnbr(long n);
void			ft_putstr(char const *str);
int		        sum_matrix(int **matrix, int r, int c);
int 	        sum_array(int *arr, int n);

// utils_euler.c
void            print_euler_tour_edges(Node *tour);
void            print_euler_tour_vertices(Node *tour, Vertex **vs);
void            euler_tour_to_edge_list(Node *tour, int **edges, int *edge_count);
int             is_euler_tour(Node *tour, Vertex **vs, int n);
int             write_euler_tour_vertices(Node *tour, Vertex **vs, const char *filename);

// utils_free.c
void			free_edge_list(Edge *head);
void			free_node_list(Node *head);
void			free_vertex(Vertex *vertex);
void			free_vertex_array(Vertex **vs, int n);

// utils_print.c
void 			print_matrix(int **matrix, int r, int c);
void			print_array_int(int *arr, int n);

// utils_lists.c
Node			*create_node(int edge_id);
void			append_node(Node **head, Node *new_node);
void			insert_node_after(Node *pos, Node *new_node);
Node 			*get_last_node(Node *head);

#endif
