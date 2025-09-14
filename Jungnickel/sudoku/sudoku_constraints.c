#include "sudoku.h"

void init_masks(int **matrix, int n, t_sudoku_masks *masks)
{
	int row, col, num;
	int i;

	for (i = 0; i < SUDOKU_SIZE; i++)
	{
		masks->row_masks[i] = 0;
		masks->col_masks[i] = 0;
		masks->box_masks[i] = 0;
	}

	for (row = 0; row < n; row++)
	{
		for (col = 0; col < n; col++)
		{
			num = matrix[row][col];
			if (num != SUDOKU_EMPTY_CELL)
				update_masks_add(row, col, num, masks);
		}
	}
}

void update_masks_add(int row, int col, int num, t_sudoku_masks *masks)
{
	int box_index;

	if (!is_valid_position(row, col) ||
		!is_valid_number(num))
		return ;

	box_index = get_box_index(row, col);
	SET_BIT(masks->row_masks[row], NUM_TO_BIT(num));
	SET_BIT(masks->col_masks[col], NUM_TO_BIT(num));
	SET_BIT(masks->box_masks[box_index], NUM_TO_BIT(num));
}

void update_masks_remove(int row, int col, int num, t_sudoku_masks *masks)
{
	int box_index;

	if (!is_valid_position(row, col) ||
		!is_valid_number(num))
		return ;

	box_index = get_box_index(row, col);
	CLEAR_BIT(masks->row_masks[row], NUM_TO_BIT(num));
	CLEAR_BIT(masks->col_masks[col], NUM_TO_BIT(num));
	CLEAR_BIT(masks->box_masks[box_index], NUM_TO_BIT(num));
}

sudoku_mask get_forbidden_mask(int row, int col, t_sudoku_masks *masks)
{
	int box_index;
	sudoku_mask used_mask;

	if (!is_valid_position(row, col))
		return (0);

	box_index = get_box_index(row, col);
	used_mask = masks->row_masks[row] |
				masks->col_masks[col] |
				masks->box_masks[box_index];

	return used_mask;
}

int can_place_number(int row, int col, int num, t_sudoku_masks *masks)
{
    sudoku_mask forbidden;

    if (!is_valid_position(row, col) || !is_valid_number(num))
        return (0);

    forbidden = get_forbidden_mask(row, col, masks);
    if (CHECK_BIT(forbidden, NUM_TO_BIT(num)))
        return (0);

    return (1);  // 配置可能
}
