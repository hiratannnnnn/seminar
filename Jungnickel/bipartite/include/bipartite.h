#ifndef BIPARTITE_H
# define BIPARTITE_H

# include <math.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include <float.h>

size_t		mem;
size_t		mem_peak;
clock_t 	proc_start;
clock_t		proc_end;

typedef struct 	Hungarian_ctx
{
	int 	n;
	double 	*u;
	double 	*v;
	int 	*p;
	int 	*way;
	double 	*minv;
	int 	*used;
}				Hungarian_ctx;

// gen_matrix.c
int		**gen_matrix_int			(int r, int c);
double 	**gen_matrix_double		(int r, int c);

// rand_bigraph.c
int 	**gen_rand_bigraph		(int a, int b, double edge_prob);

// rand_bigraph_cost.c
double 	**gen_rand_bigraph_cost	(int a, int b);

// kuhn.c
int 	max_bipartite_matching			(int **adj, int a, int b, int *match_to);

// hungarian.c
double 	hungarian			(double **cost, int a, int b, int *match_to);

// free.c
void	free_array_int		(int *ptr, int const c);
void 	free_matrix_int		(int **matrix, int const r, int const c);
void	free_array_double	(double *ptr, int const c);
void	free_matrix_double	(double **matrix, int const r, int const c);
void	free_array_char		(char *ptr, int n);

// utils_print.c
void	print_array_int		(int *arr, int const n);
void	print_matrix_int	(int **matrix, int const r, int const c);
void 	print_array_double	(double *arr, int const c);
void	print_matrix_double	(double **matrix, int const r, int const c);
void	print_info			( );

// utils_read.c
int 	**read_matrix		(int *a, int *b, char const *filename);
double 	**read_double_matrix(int *r, int *c, char const *filename);

// utils.c
int		print_hungarian_check	(double **matrix, int *match_to, int n, int indent);

// xmalloc.c
void	*xmalloc		(size_t size);
void	*xcalloc		(int n, size_t size_each);
void	xfree			(void *ptr, size_t size);

#endif
