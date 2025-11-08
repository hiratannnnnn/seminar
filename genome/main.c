// filepath: $(pwd)/genome/main.c
#include "genome.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

void 	print_array_exts(Extremity *exts, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		printf("(%d, %d)\n", exts[i * 2].gene_id, exts[i * 2 + 1].gene_id);
		i++;
	}
}

Extremity *perm_to_exts(int *perm, int n)
{
	Extremity *exts;
	int i, g_id;

	exts = (Extremity *)xmalloc(sizeof(Extremity) * (n * 2));
	if (!exts)
		return (NULL);
	printf("sizeof(Extremity): %d\n", sizeof(Extremity));
	i = 0;
	while (i < n)
	{
		g_id = abs(perm[i]);
		exts[2 * (g_id - 1)].gene_id = g_id;
		exts[2 * (g_id - 1)].sign = -1;
		exts[2 * (g_id - 1)].reality = NULL;
		exts[2 * (g_id - 1)].desire = NULL;
		exts[2 * (g_id - 1) + 1].gene_id = g_id;
		exts[2 * (g_id - 1) + 1].sign = 1;
		exts[2 * (g_id - 1) + 1].reality = NULL;
		exts[2 * (g_id - 1) + 1].desire = NULL;
		i++;
	}
	i = 0;
	while (i < n - 1)
	{
		int g1 = perm[i];
		int g2 = perm[i + 1];
		Extremity *right_of_g1, *left_of_g2;
		right_of_g1 = (g1 > 0) ?
			&exts[2 * (abs(g1) - 1) + 1] :
			&exts[2 * (abs(g1) - 1)];
		left_of_g2 = (g2 > 0) ?
			&exts[2 * (abs(g2) - 1)] :
			&exts[2 * (abs(g2) - 1) + 1];
		right_of_g1->reality = left_of_g2;
		left_of_g2->reality = right_of_g1;
	}
	// int g_first = perm[0];
	// int g_last = perm[n - 1];
	// Extremity *leftmost, *rightmost;
	// leftmost = (g_first > 0) ?
	// 	&exts[2 * (abs(g_first) - 1)] :
	// 	&exts[2 * (abs(g_first) - 1) + 1];
	// rightmost = (g_last > 0) ?
	// 	&exts[2 * (abs(g_last) - 1) + 1] :
	// 	&exts[2 * (abs(g_last) - 1)];
	return (exts);
}

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	int *perm;
	int n;
	Extremity *exts;

	n = 7;
	perm = gen_unsigned_perm(n);
	perm = add_extremity(perm, &n);

	print_array_int(perm, n, 2);
	printf("rev 1 4\n");
	rev(perm, 1, 4, n);
	print_array_int(perm, n, 2);
	printf("transpose 1 3 7\n");
	transpose(perm, 1, 3, 7, n);
	print_array_int(perm, n, 2);
	// block_interchange(perm, 1, 3, 5, 8, n);

	exts = perm_to_exts(perm, n);
	// free

	free_array_int(perm, n);
	print_info();
	return (0);
}
