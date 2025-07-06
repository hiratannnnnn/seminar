#ifndef LIB_H
# define LIB_H

# include <math.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <float.h>
# include "types.h"

extern	size_t		mem;
extern	size_t		mem_peak;
extern	clock_t 	proc_start;
extern	clock_t		proc_end;

/* ========= Matrix Operations =========*/

// generate_matrix_int.c
int			**generate_matrix_int	(int r, int c);									// ok
int			**copy_matrix_int			(int **matrix, int r, int c); 					// ok

// generate_matrix_double.c
double 		**generate_matrix_double	(int r, int c);

// matrix_basic.c
void		identity_matrix			(int **matrix, int n);
void		permutation_matrix		(int **matrix, int n, int i, int j);
void		matrix_multiply			(int **A, int **B, int **C, int n);
void		swap_vertex				(int **matrix, int n, int i, int j);

/* ========= Graph Generation =========*/

// random_bigraph_cost.c

int		 	max_bipartite_matching		(int **adj, int a, int b, int *match_to);
double 		**generate_random_bigraph_cost(int a, int b);

// random_bigraph.c
int 		**generate_random_bigraph	(int a, int b, double edge_prob);

// random_digraph_cost.c
double 		**generate_random_digraph_dbcost(int n, double max);
int 		**generate_random_digraph_intcost(int n, int max);

// random_digraph.c
int 		**generate_random_digraph	(int n, double edge_prob);					// ok
int			**generate_random_DAG		(int n, double edge_prob);					// ok

// random_euler.c

int 		**generate_random_euler		(int n, double edge_ratio);
int			make_eulerian				(int **matrix, int n, double edge_ratio);

// random_undigraph_cost.c
double 		**generate_random_undigraph_dbcost(int n, double max);
int			**generate_random_undigraph_intcost(int n, int max);

// random_undigraph.c
int 		**generate_random_undigraph		(int n, double edge_prob);					// ok, maybe name

// random_tree.c
int			*generate_random_prufer	(int n);					// ok, but maybe still can be generalized
int 		*count_degrees_from		(const int *prufer, int n);				// can be static
int 		**generate_random_tree	(int n);										// ok
void		build_tree_from			(int **matrix, int *prufer, int *degree, int n);// ok

/* ========= Graph Analysis =========*/

// graph_analysis.c
int     	need_double_edge			(int *degree, int n);
int			count_edges					(int *degree, int n);
int			is_tree						(int **matrix, int n);					// ok, but when use?
void		compute_degrees				(int **matrix, int n, int *degree);		// ok
int			find_odd_vertices			(int *degree, int n, int *odd_list);	// ok, but too narrow?
void		compute_degrees_from_list	(Vertex **vs, int n, int *degree);		// ok?

/* ========= Path Finding =========*/

// find_hamilton_cycle.c
int 		find_hamilton_cycle			(Vertex **vs, int n);

/* ========= Graph Format Conversion =========*/

// graph_conversion.c
Vertex		**adj_matrix_to_vertices	(int **matrix, int n, int undirected);	// ok
Vertex      **cost_matrix_to_vertices	(double **matrix, int n, int undirected);
int			**vertices_to_adj_matrix	(Vertex **vertices, int n);				// ok
int 		**comp_adj_matrix			(int **matrix, int n);
Vertex 		**comp_adj_list				(int **matrix, int n, int undir);
int			**dbcost_to_adj				(int **cost, int n);

// utils_edge_list.c
Node		*edge_list_from_adj_list	(Vertex **vs, int n, int is_undir);		// ok?
size_t		count_nodes					(Node *head);							// ok, name?

// line_graph.c
int			**line_graph_from_adj_list	(Vertex **vs, int n, char ***names, int *size, int is_undir); // ok?

/* ========= Input Processing =========*/

// read_matrix.c
int 		**read_adj			(int *n, char const *filename);						// ok
int 		**read_list			(int *n, char const *filename);
int 		**read_matrix		(int *a, int *b, char const *filename);
double 		**read_double_matrix(int *r, int *c, char const *filename);			// ok

/* ========= Algorithms =========*/

// algo_euler.c
void		algo_euler		(Vertex **vs, int n, int s, Node **K);				// ok

/* ========= Sorting =========*/
// cmp.c
int 	cmp_int_desc		(int a, int b);
int 	cmp_int_asc			(int a, int b);
int 	cmp_int_bogo		(int a, int b);

// sort_edge_list.c
void	sort_list			(Edge **head, int (*cmp)(int, int));
void	sort_list_by_degree	(Edge **head, int *degree, int (*cmp)(int, int));


/* ========= Utilities =========*/

// utils_edges.c
// Edge		*create_edge			(int id, int from, int to);					// ok
// int 		len_edge_list			(Edge *head);								// ok, scattered functions
// void		add_directed_edge		(Vertex **vs, int from, int to, int edge_id);	// edge_id?
// void		add_undirected_edge		(Vertex **vs, int from, int to, int edge_id);	// edge_id?
Edge		*create_edge			(int id, int from, int to, double cost);					// ok
int 		len_edge_list			(Edge *head);								// ok, scattered functions
void		add_directed_edge		(Vertex **vs, int from, int to, int edge_id, double cost);	// edge_id?
void		add_undirected_edge		(Vertex **vs, int from, int to, int edge_id, double cost);	// edge_id?

// utils_vertex.c
Vertex		*create_vertex			(int id);									// ok
Vertex		**create_vertex_array	(int n);									// ok

/* ========= Euler Tour Utilities =========*/

// utils_basic.c
void		ft_putnbr		(long n);											// deprecated
void		ft_putstr		(char const *str);									// deprecated
int			sum_matrix		(int **matrix, int r, int c);						// ok
int			sum_array		(int *arr, int n);									// ok

// utils_char.c
void	 	free_array_char				(char **ss, int n);						// ok
int 		count_digit					(int number);					// ok

// utils_edge_list.c
Node		*edge_list_from_adj_list	(Vertex **vs, int n, int is_undir);		// fine

// utils_free.c
void		free_array_int		(int *ptr, int const n);
void		free_matrix_int		(int **matrix, int const r, int const c);
void		free_array_double	(double *ptr, int const c);
void		free_matrix_double	(double **matrix, int const r, int const c);
void		free_edge_list		(Edge *head);					// ok, but directory messy?
void		free_node_list		(Node *head);					// ok
void		free_vertex			(Vertex *vertex);				// ok
void		free_vertex_array	(Vertex **vs, int n);			// ok

// utils_hamilton.c
int			**closure_of		(int **matrix, int n);			// ok


// utils_node.c
Node		*create_node		(Edge *edge);					// ok
void		append_node			(Node **head, Node *new_node);
void		insert_node_after	(Node *pos, Node *new_node);
Node 		*get_last_node		(Node *head);
Node	 	*node_pop_first		(Node **head);


// utils_pathnode.c
PathNode	*create_pathnode	(Vertex *vertex);
void		append_pathnode		(PathNode **head, PathNode *new_pathnode);
void		insert_pathnode_after(PathNode *pos, PathNode *new_pathnode);
PathNode	*get_last_pathnode	(PathNode *head);
PathNode 	*pathnode_pop_first	(PathNode **head);
void		pathnode_pop_last	(PathNode **head);
int 		pathnode_length		(PathNode *head);
void		free_path			(PathNode **head);

// utils_math.c
int			*random_perm		(int n);

// utils_array.c
int			max_of_array		(int *arr, int n);
int			min_of_array		(int *arr, int n);

// utils_print.c
void 		print_matrix_int	(int **matrix, int r, int c);
void		print_array_int		(int *arr, int n, int max_width);
void		print_matrix_double			(double **matrix, int r, int c, int precision);
void 		print_array_double			(double *arr, int c, int max_width, int precision);
void		print_vertex		(Vertex *v);
void		print_vertices		(Vertex **vs, int n);
void		print_edge_list		(Edge *head);
void 		print_path_node		(PathNode *head);
void		print_array_char	(char **ss, int n);
void		print_info			(	);

// write_to_file.c
int			write_adjacent_matrix	(int **matrix, int n, char const *filename);	// ok
int 		write_adjacent_list		(int **matrix, int n, char const *filename);	// ok
int 		write_path_node			(PathNode *head, char const *filename);
int 		write_double_matrix		(double **matrix, int r, int c, char const *filename);
void 		save_some_matrix		(int n, double edge_prob,						// ok
	int **(*gen_some_mat)(int, double), char const *filename);

/* ========= Strings ========= */

// ft_split.c
char 		**ft_split			(char const *str, char *sep);

// ft_strdup.c
char		*ft_strdup			(const char *s);

// ft_strtrim.c
char 		*ft_strtrim			(char const *str, char const *set);


/* ========= Memory Allocation ========= */

// xmalloc.c
void		*xmalloc			(size_t size);
void		*xcalloc			(int n, size_t size_each);
void		xfree				(void *ptr, size_t size);

#endif
