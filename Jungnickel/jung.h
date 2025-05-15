#ifndef JUNG_H
# define JUNG_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		*count_degrees(int *prufer, int n);

// generate_adj.c
int		**generate_adj(int r, int c);

int		*generate_prufer_code(int *degrees, int n);

int		**generate_matrix(int *degs, int n);

void	draw_graph(int **matrix, int n);

int		is_tree(int **matrix, int n);

int		find_min_vertex(int *degs, int n);

int		find_max_vertex(int *degs, int n, int exclude);

int		find_min(int *prufer, int *appeared, int vertices, int n,
			int current_index);

// utils_free.c
void	free_array_int(int **arr, const int r);

// utils.c
void	ft_putnbr(long n);
void	ft_putstr(char const *str);

#endif
