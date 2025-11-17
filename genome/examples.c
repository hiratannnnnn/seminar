#include "genome.h"

int write_perm_ext(int *perm, int n, double cut_prob, char const *filename)
{
    FILE *fp;
    int i;

    if (!perm || n <= 0)
        return (-2);
    fp = fopen(filename, "w");
    if (!fp)
    {
        printf("Failed to open file %s\n", filename);
        return (-1);
    }
    fprintf(fp, "%d\n", n);
    for (i = 0; i < n; i++)
	{
        fprintf(fp, "%d%c", perm[i], (i == n - 1) ? '\n' : ' ');
		if (i < n - 1)
			if ((double)rand() / RAND_MAX < cut_prob)
				fprintf(fp, "^ ");
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%d%c", i+1, (i == n - 1) ? '\n' : ' ');
		if (i < n - 1)
			if ((double)rand() / RAND_MAX < cut_prob)
				fprintf(fp, "^ ");
	}
    fclose(fp);
    return (0);
}

int make_example(int n, char const *filename, double cut_prob)
{
    int *perm;

    perm = gen_signed_perm(n);
    write_perm_ext(perm, n, cut_prob, filename);
    print_array_int(perm, n, 4);
	free_array_int(perm, n);
    return (1);
}