#include <stdio.h>
#include <stdlib.h>

int	*generate_prufer_code(int *degrees, int vertices)
{
	int	n;
	int	*prufer;
	int	idx;

	n = vertices - 2;
	prufer = (int *)malloc(sizeof(int) * n);
	idx = 0;
	for (int i = 0; i < vertices; i++)
	{
		for (int j = 1; j < degrees[i]; j++)
		{
			prufer[idx++] = i;
		}
	}
	return (prufer);
}

int	main(int argc, char *argv[])
{
	int vertices, *degrees, *prufer, i, sum = 0;

	if (argc < 2)
	{
		int default_degrees[] = {1, 1, 1, 4, 2, 1};
		vertices = sizeof(default_degrees) / sizeof(int);
		degrees = (int *)malloc(sizeof(int) * vertices);
		for (i = 0; i < vertices; i++)
			degrees[i] = default_degrees[i];
	}
	else
	{
		vertices = argc - 1;
		degrees = (int *)malloc(sizeof(int) * vertices);
		for (i = 0; i < vertices; i++)
			degrees[i] = atoi(argv[i + 1]);
	}

	for (i = 0; i < vertices; i++)
		sum += degrees[i];

	if (sum != 2 * (vertices - 1))
	{
		printf("Error: sum of degrees (%d) != 2(n-1) = %d\n", sum, 2 * (vertices
				- 1));
		free(degrees);
		return (1);
	}

	printf("Degrees: ");
	for (i = 0; i < vertices; i++)
		printf("%d ", degrees[i]);
	printf("\n");

	prufer = generate_prufer_code(degrees, vertices);

	printf("Prufer code: ");
	for (i = 0; i < vertices - 2; i++)
		printf("%d ", prufer[i] + 1); // 1-indexed
	printf("\n");

	free(degrees);
	free(prufer);
	return (0);
}
