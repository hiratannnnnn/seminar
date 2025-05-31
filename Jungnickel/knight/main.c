#include "lib.h"

size_t 		mem = 0;
size_t 		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

/**
 * @brief For given dimensions (r, c), determines if a knight (from chess)
 * can visit all squares of an (r, c) rectangular board.;
 */

int main(int ac, char **av)
{
	if (ac != 3)
	{
		printf("Usage: ./a.out <r> <c>\n");
		return (1);
	}
	int r = atoi(av[1]);
	int c = atoi(av[2]);
	int **matrix = generate_matrix(r, c); // r * c


	print_info();
	return (0);
}


// int main(int ac, char **av)
// {
// 	(void)ac;
// 	printf("%d", count_digit(atoi(av[1])));
// 	return (0);
// }
