#include "euler.h"

size_t	    mem 		= 0;
size_t	    mem_peak 	= 0;
clock_t     proc_start;
clock_t     proc_end;   

int main(void)
{
    proc_start = clock();


    int **matrix;
    int n;

    n = 12;
    // create tree from prufer code
    matrix = generate_random_tree(n);
    // make the tree eulerian

    make_eulerian(matrix, n);

    // free
    print_matrix(matrix, n, n);
    free_matrix_int(matrix, n, n);
    proc_end = clock();
    print_info();
    return (0);
}
