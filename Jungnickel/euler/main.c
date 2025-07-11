#include "euler.h"

size_t	    mem 		= 0;
size_t	    mem_peak 	= 0;
clock_t     proc_start;
clock_t     proc_end;

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    proc_start = clock();

    int **matrix;
    int n = 12;

    matrix = gen_rand_tree(n);
    print_matrix_int(matrix, n, n);
    make_eulerian(matrix, n, 1.0);

    // free
    print_matrix_int(matrix, n, n);
    free_matrix_int(matrix, n, n);
    print_info();
    return (0);
}
