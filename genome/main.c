// filepath: $(pwd)/genome/main.c
#include "genome.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	int *perm;
	int n;

	/* for generating some permutation.
	// n = 100;
	// perm = gen_signed_perm(n);
	// write_perm(perm, n, "long_perm.txt");
	// print_array_int(perm, n, 4);
	*/
	// perm = read_perm("long_perm.txt", &n);
	perm = read_perm("read.txt", &n);
	// perm = add_extremity(perm, &n);

	print_array_int(perm, n, 2);
	// printf("rev 1 4\n");
	// rev(perm, 1, 4, n);
	// print_array_int(perm, n, 2);
	// printf("transpose 1 3 7\n");
	// transpose(perm, 1, 3, 7, n);
	// print_array_int(perm, n, 2);
	solve_dcj(perm, n);

	free_array_int(perm, n);
	print_info();
	return (0);
}
