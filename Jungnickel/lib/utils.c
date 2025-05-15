#include "../jung.h"

void	ft_putnbr(long n)
{
	long long	num;
	char		c;

	num = (long long)n;
	if (num < 0)
	{
		num = -num;
		write(1, "-", 1);
	}
	if (num >= 10)
		ft_putnbr(num / 10);
	c = num % 10 + '0';
	write(1, &c, 1);
}

void	ft_putstr(char const *str)
{
	while (*str)
		write(1, str++, 1);
}

// int	main(void)
// {
// 	int	n;

// 	n = 1123412341;
// 	ft_putnbr(n);
// 	return (0);
// }
