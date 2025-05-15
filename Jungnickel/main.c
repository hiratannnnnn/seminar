#include "jung.h"

int	main(void)
{
	const int	r = 3;
	const int	c = 5;
	int			**result;

	result = generate_adj(r, c);
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
			ft_putnbr(result[i][j]);
		ft_putstr("\n");
	}
}

