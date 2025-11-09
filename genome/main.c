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
	Extremity_ctx ctx;
	Extremity **exts;

	n = 7;
	perm = gen_unsigned_perm(n);
	// perm = add_extremity(perm, &n);

	print_array_int(perm, n, 2);
	printf("rev 1 4\n");
	rev(perm, 1, 4, n);
	print_array_int(perm, n, 2);
	printf("transpose 1 3 7\n");
	transpose(perm, 1, 3, 7, n);
	print_array_int(perm, n, 2);
	// block_interchange(perm, 1, 3, 5, 8, n);
	printf("n: %d\n", n);
	printf("init: %d\n", Extremity_init(&ctx, perm, n));
	exts = ctx.exts;
	print_array_exts(exts, n);
	// free

	// free_array_exts(exts, n);
	Extremity_free(&ctx, n);
	free_array_int(perm, n);
	print_info();
	return (0);
}
