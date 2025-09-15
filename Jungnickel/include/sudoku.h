#ifndef SUDOKU_H
# define SUDOKU_H

# include "lib.h"

/* ========= Consants and Macros ========= */

# define SUDOKU_SIZE			9
# define SUDOKU_BOX_SIZE		3
# define SUDOKU_EMPTY_CELL		0
# define SUDOKU_ALL_CANDIDATES	0b000000000

// bit shifting
# define SET_BIT(mask, pos)		((mask) |= (1 << (pos)))
# define CLEAR_BIT(mask, pos)	((mask) &= ~(1 << (pos)))
# define CHECK_BIT(mask, pos)	((mask) & (1 << (pos)))
# define COUNT_BITS(mask)		(popcount_manual(mask))

# define NUM_TO_BIT(num)		((num) - 1)
# define BIT_TO_NUM(bit)		((bit) + 1)

typedef uint16_t sudoku_mask;

typedef struct s_sudoku_masks
{
	sudoku_mask row_masks[SUDOKU_SIZE];
	sudoku_mask col_masks[SUDOKU_SIZE];
	sudoku_mask box_masks[SUDOKU_SIZE];
}				t_sudoku_masks;

// solve_sudoku.c
void solve_sudoku(int **board, int n);

// utils_constraints.c

void		init_masks				(int **board, int n, t_sudoku_masks *masks);
void		update_masks_add		(int row, int col, int num, t_sudoku_masks *masks);
void		update_masks_remove		(int row, int col, int num, t_sudoku_masks *masks);
sudoku_mask	get_forbidden_mask		(int row, int col, t_sudoku_masks *masks);
int			can_place_number		(int row, int col, int num, t_sudoku_masks *masks);

// utils_analysis.c
int			find_empty_cell			(int **board, int n, int *row, int *col);
// int			find_best_cell			(int **board, int n, int *row, int *col);
// int			is_puzzle_valid			(int **board, int n);
int			is_puzzle_completed		(int **board, int n);
// int 		has_unique_solution		(int **board, int n);

// utils_strategies.c
int			solve_backtracking		(int **board, int n, t_sudoku_masks *masks);
// int			solve_naked_singles		(int **board, int n, t_sudoku_masks *masks);
// int			solve_basic_elimination	(int **board, int n, t_sudoku_masks *masks);
// int			solve_hybrid			(int **board, int n, t_sudoku_masks *masks);

// utils_utils.c
int			get_box_index			(int row, int col);
// void		get_box_start			(int box_index,  int *start_row, int *start_col);
int			is_valid_position		(int row, int col);
int			is_valid_number			(int num);
int			popcount_manual			(unsigned int mask);

// utils_print.c
void		print_mask_binary		(sudoku_mask mask, const char *label);
void		print_mask_candidates	(sudoku_mask mask, const char *label);
void		print_masks_status		(t_sudoku_masks *masks);
void		print_masks_candidates	(t_sudoku_masks *masks);

// utils_debug.c
// void		print_sudoku_grid		(int **board, int n);
// void		print_constraints_status(void);
// void		print_available_numbers	(int row, int col);
// void		print_solving_step		(int **board, int n, const char *label);

// utils_generator.c
// void		generate_empty_grid		(int **board, int n);
// void		generate_solved_grid	(int **board, int n);
// void 		generate_puzzle			(int **board, int n, int difficulty);
// int			remove_numbers_sym		(int **board, int n, int count);


#endif
