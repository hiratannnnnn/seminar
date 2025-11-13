#include "genome.h"

static void	put_nums(int *perm, char *line, int n)
{
	int i;
	char *cur, *endptr;

	i = 0;
	cur = line;
	while (i < n)
	{
		while (*cur == ' ' || *cur == '\n' || *cur == '^')
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
	free(line);
	close(fd);
	return (perm);
}

// static int count_numbers(char const *line)
// {
// 	int count;
// 	char const *cur;

// 	count = 0;
// 	cur = line;
// 	while(*cur)
// 	{
// 		while (*cur == ' ' || *cur == '\n' || *cur == '^')
// 			cur++;
// 		if (!*cur)
// 			break;
// 		strtol(cur, (char **)&cur, 10);
// 		count++;
// 	}
// 	return (count);
// }

static void	cut_line(Extremity_ctx *ctx, Extremity **exts, char const *line, int n)
{
	int i, tmp;
	char *cur, *endptr;
	Extremity *ext;

	i = 0;
	tmp = INT_MIN;
	cur = (char *)line;
	while (i < n)
	{
		while (*cur == ' ' || *cur == '\n')
			cur++;
		if (!*cur)
			break;
		if (*cur == '^')
		{
			ext = get_ext_by_value(ctx, exts, tmp);
			cut_exts(ctx, ext, ext->reality);
			cur++;
		}
		else
		{
			tmp = (int)strtol(cur, &endptr, 10);
			cur = endptr;
			i++;
		}
	}
}

static int count_centinels(char const *line)
{
	char *str;
	int count;

	str = (char *)line;
	count = 1;
	while (*str)
	{
		if (*str == '^')
			count++;
		str++;
	}
	return (count);
}

static void	put_nums_centinels(int *perm, int *perm_cent, int *sigma_cent, char const *line, int n)
{
	int i, j, tmp;
	char *cur, *endptr;

	i = 0;
	j = 0;
	cur = (char *)line;
	perm_cent[j] = 0;
	sigma_cent[j] = 1;
	j++;
	while (i < n)
	{
		while (*cur == ' ' || *cur == '\n')
			cur++;
		if (!*cur)
			break;
		if (*cur == '^')
		{
			perm_cent[j] = n + 1;
			sigma_cent[j] = 1;
			j++;
			perm_cent[j] = 0;
			sigma_cent[j] = 1;
			j++;
			cur = cur + 1;
		}
		tmp = (int)strtol(cur, &endptr, 10);
		printf("%d ", tmp);
		perm_cent[j] = abs(perm[i]);
		sigma_cent[j] = abs(perm[i]) / perm[i];
		i++;
		j++;
		cur = endptr;
	}
	perm_cent[j] = n + 1;
	sigma_cent[j] = 1;
}

int	read_exts(char const *filename, Extremity_ctx *ctx, int *n)
{
	int fd;
	int c_cent;
	int *perm, *perm_cent, *sigma_cent, *id_perm;
	char *line;

	fd = open(filename, O_RDONLY);
	if (fd < 3)
		return (printf("Wrong file.\n"), -1);
	line = get_next_line(fd);
	*n = atoi(line);
	ctx->n = *n;
	free(line);
	if (*n < 0)
		return (printf("Wrong size.\n"), -1);
	perm = (int *)xmalloc(sizeof(int) * (*n));
	if (!perm)
		return (printf("Malloc Error.\n"), -1);
	line = get_next_line(fd);
	printf("%s", line);
	put_nums(perm, line, *n);
	ctx->perm = perm;
	// print_array_int(perm, *n, 2);
	c_cent = count_centinels(line);
	ctx->n_cent = ctx->n + c_cent * 2;
	perm_cent = (int *)xmalloc(sizeof(int) * (ctx->n_cent));
	sigma_cent = (int *)xmalloc(sizeof(int) * (ctx->n_cent));
	if (!perm_cent || !sigma_cent)
		return (printf("Malloc Error.\n"), -1);
	put_nums_centinels(perm, perm_cent, sigma_cent, line, ctx->n);
	// print_array_int(perm_cent, ctx->n_cent, 2);
	// print_array_int(sigma_cent, ctx->n_cent, 2);
	ctx->perm_cent = perm_cent;
	ctx->sigma_cent = sigma_cent;
	ctx->exts = perm_to_exts(perm, *n);
	ctx->ext_l = create_ext(0, 1);
	if (!ctx->ext_l)
		return (-1);
	ctx->ext_r = create_ext(*n + 1, -1);
	if (!ctx->ext_r)
		return (-1);
	put_realities(ctx, ctx->exts, ctx->ext_l, ctx->ext_r, perm, *n);
	put_desires(ctx->exts, ctx->ext_l, ctx->ext_r, *n);
	cut_line(ctx, ctx->exts, line, *n);
	free(line);
	line = get_next_line(fd);
	printf("%s", line);
	id_perm = gen_id_perm(*n);
	ctx->goals = perm_to_exts(id_perm, *n);
	ctx->goal_l = create_ext(0, 1);
	if (!ctx->goal_l)
		return (-1);
	ctx->goal_r = create_ext(*n + 1, -1);
	if (!ctx->goal_r)
		return (-1);
	put_realities(ctx, ctx->goals, ctx->goal_l, ctx->goal_r, id_perm, *n);
	put_desires(ctx->goals, ctx->goal_l, ctx->goal_r, *n);
	cut_line(ctx, ctx->goals, line, *n);
	free(line);
	close(fd);
	ctx->head = create_component();
	free_array_int(id_perm, *n);
	return (1);
}
