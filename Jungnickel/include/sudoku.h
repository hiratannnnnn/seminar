#ifndef SUDOKU_H
# define SUDOKU_H

# include "lib.h"

typedef uint16_t sudoku_mask;

void solve_sudoku(int **matrix, int n);

#endif
