// filepath: /c/Users/PC_User/seminar/Jungnickel/mintree/main.c
#include "mintree.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

    double **cost;
	int n;
	n = 10;

    cost = gen_rand_undigraph_dbcost(n, 0, 30, 0.6);
    if (!cost)
        return (1);
    print_matrix_double(cost, n, n, 3);
    nl(2);
    solve_steiner(cost, n);

    free_matrix_double(cost, n, n);
	print_info();
	return (0);
}
