#include "knight.h"

void	set_board_knight(int **matrix, int const r, int const c)
{
	int i;
	int n;
	int x, y;
	int to;

	n = r * c;
	for (i = 0; i < n - r; i++) 	// skip last 1 row for a tiny bit of efficiency
	{
		x = i % r;
		y = i / r;
		if (0 <= x - 2)						// left lower
		{
			to = y * r + x;
			to += r - 2;
			matrix[i][to] = matrix[to][i] = 1;
		}
		if (x + 2 < r)						// right lower
		{
			to = y * r + x;
			to += r + 2;
			matrix[i][to] = matrix[to][i] = 1;
		}
		if ((0 <= x - 1) && (y + 2 < c)) 	// left higher
		{
			to = y * r + x;
			to += r + r - 1;
			matrix[i][to] = matrix[to][i] = 1;
		}
		if ((x + 1 < r) && (y + 2 < c))		// right higher
		{
			to = y * r + x;
			to += r + r + 1;
			matrix[i][to] = matrix[to][i] = 1;
		}
	}
}
