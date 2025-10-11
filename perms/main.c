// filepath: $(pwd)/perms/main.c
#include "perms.h"

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
	// perm = gen_perm(-7, 7, &n);
	perm = gen_unsigned_perm(n);

	perm = add_extremity(perm, &n);
	perm = add_pairs(perm, &n);
	print_array_int(perm, n, 3);
	// free
	free_array_int(perm, n);
	print_info();
	return (0);
}
