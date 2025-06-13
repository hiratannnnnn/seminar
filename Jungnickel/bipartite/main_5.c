#include "bipartite.h"

static char *init_filename()
{
	char *filename;

	filename = (char *)xmalloc(sizeof(char) * (7));
	if (!filename)
		return (NULL);
	filename[0] = 'b';
	filename[1] = '0';
	filename[2] = '.';
	filename[3] = 't';
	filename[4] = 'x';
	filename[5] = 't';
	filename[6] = '\0';
	return filename;
}

int main(void)
{
	proc_start = clock();

	double **matrix;
	int *match_to;
	char *filename;
	int a, b, i;
	clock_t now;

	filename = init_filename();
	for (i = 1; i <= 5; i++)
	{
		now = clock();
		filename[1] = '0' + i;
		matrix = read_double_matrix(&a, &b, filename);
		match_to = (int *)xcalloc(b, sizeof(int));
		printf("reading %s, (%d, %d), n^2 * m = %zu\n", filename, a, b, (unsigned long)(a + b) * (a + b) * (a * b / 2));
		printf("%f\n", hungarian(matrix, a, b, match_to));
		printf("time: %f\n\n", (double)(clock() - now) / CLOCKS_PER_SEC);
		// printf("%d\n", print_hungarian_check(matrix, match_to, b, 10));
		free_matrix_double(matrix, a, b);
		free_array_int(match_to, b);
	}

	free_array_char(filename, 6);

	proc_end = clock();
	print_info();
	return (0);
}
