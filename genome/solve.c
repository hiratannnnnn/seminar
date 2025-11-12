# include "genome.h"

int solve_dcj(Extremity_ctx *ctx)
{
	int *maxes, *mins;
	int n;
	int n_cent;

	n = ctx->n;
	n_cent = ctx->n_cent;
	printf("n:%d, n_cent:%d\n", n, n_cent);
	// if (Extremity_init(ctx, perm, n) == -1)
	// 	return (-1);
	maxes = (int *)xmalloc(sizeof(int) * (n_cent));
	mins = (int *)xmalloc(sizeof(int) * (n_cent));
	if (!maxes || !mins)
		return (-1);
	printf("allocated arrays.\n");
	preprocess(ctx, maxes, mins);
	print_array_int(maxes, n_cent, 3);
	print_array_int(mins, n_cent, 3);

	// print_array_exts(ctx->exts, n);
	print_chromosomes(ctx, n);
	print_components(ctx->head);
	find_components_1(ctx, maxes, mins);





	// free
	Extremity_free(ctx, n);
	free_array_int(maxes, n + 2);
	free_array_int(mins, n + 2);
	return (1);
}
