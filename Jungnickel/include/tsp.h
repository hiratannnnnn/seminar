#ifndef TSP_H
# define TSP_H

# include "../../include/lib.h"

int 	**gen_weighted_matrix	(int n, int upper);

int		tsp_bruteforce(int **matrix, int n, int *best_path);
int		tsp_greedy(int **matrix, int n, int *path);

#endif
