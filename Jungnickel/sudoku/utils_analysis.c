#include "sudoku.h"

int find_empty_cell(int **board, int n, int *row, int *col)
{
	int r, c;

	for (r = 0; r < n; r++)
	{
		for (c = 0; c < n; c++)
		{
			if (board[r][c] == SUDOKU_EMPTY_CELL)
			{
				*row = r;
				*col = c;
				return (1);
			}
		}
	}
	return (0);
}

int is_puzzle_completed(int **board, int n)
{
	int row, col;

	return (!find_empty_cell(board, n, &row, &col));
}
