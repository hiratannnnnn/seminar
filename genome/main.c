// filepath: $(pwd)/genome/main.c
#include "genome.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

static void	put_nums(int *perm, char *line, int n)
{
	int i;
	char *cur, *endptr;

	i = 0;
	cur = line;
	while (i < n)
	{
		while (*cur == ' ' || *cur == '\n')
			cur++;
		if (!*cur)
			break;
		perm[i] = (int)strtol(cur, &endptr, 10);
		cur = endptr;
		i++;
	}
}

int *read_perm(char *filename, int *n)
{
	int fd;
	int *perm;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 3)
		return (printf("Wrong file.\n"), NULL);
	line = get_next_line(fd);
	printf("%s", line);
	*n = atoi(line);
	free(line);
	if (*n < 0)
		return (printf("Wrong size.\n"), NULL);
	perm = (int *)xmalloc(sizeof(int) * (*n));
	if (!perm)
		return (printf("Malloc Error.\n"), NULL);
	line = get_next_line(fd);
	printf("%s", line);
	put_nums(perm, line, *n);
	printf("finished.\n");
	free(line);
	close(fd);
	return (perm);
}

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	int *perm;
	int n;
	Extremity_ctx ctx;
	Extremity **exts;

	// n = 40;
	// perm = gen_unsigned_perm(n);
	perm = read_perm("read.txt", &n);
	// perm = add_extremity(perm, &n);

	print_array_int(perm, n, 2);
	// printf("rev 1 4\n");
	// rev(perm, 1, 4, n);
	// print_array_int(perm, n, 2);
	// printf("transpose 1 3 7\n");
	// transpose(perm, 1, 3, 7, n);
	// print_array_int(perm, n, 2);
	printf("init: %d\n", Extremity_init(&ctx, perm, n));
	exts = ctx.exts;
	print_array_exts(exts, n);
	// printf("aaa\n");
	print_chromosomes(&ctx, n);
	cut_exts(ctx.exts[6], ctx.exts[6]->reality);
	// cut_exts(ctx.exts[12], ctx.exts[12]->reality);
	// cut_exts(ctx.exts[21], ctx.exts[21]->reality);
	// cut_exts(ctx.exts[30], ctx.exts[30]->reality);
	print_chromosomes(&ctx, n);
	print_components(ctx.head);
	// free

	// free_array_exts(exts, n);
	Extremity_free(&ctx, n);
	free_array_int(perm, n);
	print_info();
	return (0);
}
