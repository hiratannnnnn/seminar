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
    int n = 30;

    matrix = generate_random_tree(n);
    print_matrix(matrix, n, n);
    printf("%d\n", make_eulerian(matrix, n));

    // free
    print_matrix(matrix, n, n);
    free_matrix_int(matrix, n, n);
    proc_end = clock();
    print_info();
    return (0);
}
