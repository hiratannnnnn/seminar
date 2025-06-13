#include "euler.h"

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
    proc_start = clock();

    int **matrix;
    int n = 12;

    matrix = generate_random_tree(n);
    print_matrix_int(matrix, n, n);
    make_eulerian(matrix, n, 1.0);

    // free
    print_matrix_int(matrix, n, n);
    free_matrix_int(matrix, n, n);
    proc_end = clock();
    print_info();
    return (0);
}
