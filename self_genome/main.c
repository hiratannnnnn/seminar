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

	Extremity_init("tests/ex_10000.txt", &ctx, &n);
	// print_Extremity_ctx(&ctx);

	proc_start = clock();
	// solve_dcj_mine(&ctx, 0);
	solve_dcj_mine(&ctx, 1);

	// TODO
	Extremity_free(&ctx, n);
	free_array_int(ctx.perm, n);
	print_info();
	return (0);
}
