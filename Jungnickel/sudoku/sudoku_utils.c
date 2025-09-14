#include "sudoku.h"

int	get_box_index(int row, int col)
{
	int r, c;
	int index;

	r = row / SUDOKU_BOX_SIZE;
	c = col / SUDOKU_BOX_SIZE;
	index = r * SUDOKU_BOX_SIZE + c;
	return index;
}

int	is_valid_position(int row, int col)
{
	if (row >= 0 &&
		row < SUDOKU_SIZE &&
		col >= 0 &&
		col < SUDOKU_SIZE)
		return (1);
	return (0);
}

int	is_valid_number(int num)
{
	if (num >= 1 && num <= SUDOKU_SIZE)
		return (1);
	return (0);
}

int	popcount_manual(unsigned int mask)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (i < SUDOKU_SIZE)
	{
		if (CHECK_BIT(mask, i))
			count++;
		i++;
	}
	return (count);
}
