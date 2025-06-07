// filepath: /c/Users/PC_User/seminar/Jungnickel/bipartite/main.c
#include "bipartite.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
    setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	double **matrix;
	int *match_to;
	int a, b;

	matrix = read_double_matrix(&a, &b, "b5.txt");
	// print_matrix_double(matrix, a, b);
	match_to = (int *)xcalloc(b, sizeof(int));
	printf("%f\n", hungarian(matrix, a, b, match_to));
	print_array_int(match_to, b);

	// free
	free_matrix_double(matrix, a, b);
	free_array_int(match_to, b);
	proc_end = clock();
	print_info();
	return (0);
}
