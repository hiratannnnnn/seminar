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

	n = 7;
	perm = gen_unsigned_perm(n);
	perm = add_extremity(perm, &n);

	print_array_int(perm, n, 2);
	rev(perm, 1, 4, n);
	// transpose(perm, 1, 3, 7, n);
	// block_interchange(perm, 1, 3, 5, 8, n);
	print_array_int(perm, n, 2);

	// free

	free_array_int(perm, n);
	print_info();
	return (0);
}
