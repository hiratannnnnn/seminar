#ifndef BIPARTITE_H
# define BIPARTITE_H

# include "lib.h"
# include <float.h>

int **generate_random_bigraph(int a, int b, double edge_prob);
int max_bipartite_matching(int **adj, int a, int b, int *match_to);
double **generate_matrix_double(int r, int c);
void	free_matrix_double(double **matrix, int const r, int const c);
double **generate_random_bigraph_cost(int a, int b);
void	print_matrix_double(double **matrix, int r, int c);
void 	print_array_double(double *arr, int c);

void	free_array_double(double *arr, int n);
double hungarian(double **cost, int a, int b, int *match_to);

#endif
