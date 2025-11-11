# include "genome.h"

int solve_dcj(int *perm, int n)
{
	Extremity_ctx ctx;
	int *maxes, *mins;

	if (Extremity_init(&ctx, perm, n) == -1)
		return (-1);
	maxes = (int *)xmalloc(sizeof(int) * (n + 2));
	mins = (int *)xmalloc(sizeof(int) * (n + 2));
	if (!maxes || !mins)
		return (-1);
	preprocess(&ctx, maxes, mins);
	print_array_int(maxes, n + 2, 3);
	print_array_int(mins, n + 2, 3);

	// print_array_exts(ctx.exts, n);
	print_chromosomes(&ctx, n);
	cut_exts(ctx.exts[6], ctx.exts[6]->reality);
	print_chromosomes(&ctx, n);
	print_components(ctx.head);

	find_components_1(&ctx, maxes, mins, n);





	// free
	Extremity_free(&ctx, n);
	free_array_int(maxes, n + 2);
	free_array_int(mins, n + 2);
	return (1);
}
