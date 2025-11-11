#include "genome.h"

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
	free(line);
	close(fd);
	return (perm);
}
