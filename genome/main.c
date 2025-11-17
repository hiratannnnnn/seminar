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
	Extremity_ctx ctx;
	int n;

	// for generating some permutation.
	// make_example(20, "tests/ex_20.txt", 0.1);
	// make_example(100, "tests/ex_100.txt", 0.1);
	// make_example(1000, "tests/ex_1000.txt", 0.1);
	// make_example(10000, "tests/ex_10000.txt", 0.1);

	
	// perm = read_perm("long_perm.txt", &n);
	// perm = read_perm("read.txt", &n);
	// read_exts("read.txt", &ctx, &n);
	read_exts("tests/ex_100.txt", &ctx, &n);
	reverse_p(&ctx, ctx.perm_cent, ctx.sigma_cent);
	reverse_p(&ctx, ctx.perm_cent, ctx.sigma_cent);


	// print_Extremity_ctx(&ctx);

	// print_array_int(perm, n, 2);
	// printf("rev 1 4\n");
	// rev(perm, 1, 4, n);
	// print_array_int(perm, n, 2);
	// printf("transpose 1 3 7\n");
	// transpose(perm, 1, 3, 7, n);
	// print_array_int(perm, n, 2);
	solve_dcj_mine(&ctx);
	// solve_dcj(&ctx);

	// TODO
	Extremity_free(&ctx, n);
	free_array_int(ctx.perm, n);
	print_info();
	return (0);
}
