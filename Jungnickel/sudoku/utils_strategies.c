#include "sudoku.h"

int solve_backtracking(int **board, int n, t_sudoku_masks *masks)
{
	int row, col, num;

	if (!find_empty_cell(board, n, &row, &col))
	{
		print_matrix_int(board, n, n);
		return (1);
	}

	for (num = 1; num <= SUDOKU_SIZE; num++)
	{
		if (can_place_number(row, col, num, masks))
		{
			printf("[DEBUG] placing %d to (%d, %d)\n",
					num, row, col);
			board[row][col] = num;
			update_masks_add(row, col, num, masks);
			if (solve_backtracking(board, n, masks))
				return (1);
			printf("<-- removing %d from (%d, %d)\n",
					num, row, col);
			board[row][col] = SUDOKU_EMPTY_CELL;
			update_masks_remove(row, col, num, masks);
		}
	}
	return (0);
}
