#ifndef EULER_H
# define EULER_H

# include "lib.h"

// algo_euler.c
void		algo_euler		(Vertex **vs, int n, int s, Node **K);

// utils_euler.c
void  		print_euler_tour_edges		(Node *tour);
void  		print_euler_tour_vertices	(Node *tour, Vertex **vs);
void  		euler_tour_to_edge_list		(Node *tour, int **edges, int *edge_count);
int   		is_euler_tour				(Node *tour, Vertex **vs, int n);
int   		write_euler_tour_vertices	(Node *tour, Vertex **vs, const char *filename);

#endif
