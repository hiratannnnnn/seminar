// 1-2-16.c

#include <stdio.h>
#include <stdlib.h>

int	find_min(int *prufer, int *appeared, int vertices, int n, int current_index)
{
	int	*frequency;

	frequency = (int *)malloc(sizeof(int) * vertices);
	for (int i = 0; i < vertices; i++)
		frequency[i] = 0;
	for (int i = current_index; i < n; i++)
		frequency[prufer[i]]++;
	for (int i = 0; i < vertices; i++)
	{
		if (appeared[i] == 0 && frequency[i] == 0)
		{
			appeared[i] = 1;
			free(frequency);
			return (i);
		}
	}
	free(frequency);
	return (-1);
}

int	*count_degrees(int *prufer, int n)
{
	int	i;
	int	*degrees;
	int	*appeared;
	int	vertices;
	int	min;

	vertices = n + 2;
	degrees = (int *)malloc(sizeof(int) * vertices);
	for (i = 0; i < vertices; i++)
		degrees[i] = 1;
	appeared = (int *)malloc(sizeof(int) * vertices);
	for (i = 0; i < vertices; i++)
		appeared[i] = 0;
	for (i = 0; i < n; i++)
	{
		min = find_min(prufer, appeared, vertices, n, i);
		if (min != -1)
			degrees[prufer[i]]++;
	}
	free(appeared);
	return (degrees);
}

// int	main(int argc, char *argv[])
// {
// 	int n;
// 	int *prufer;
// 	int *degrees;
// 	int vertices;
// 	int i;

// 	if (argc < 2)
// 	{
// 		int prufer_1indexed[] = {4, 4, 4, 5};
// 		n = sizeof(prufer_1indexed) / sizeof(prufer_1indexed[0]);
// 		prufer = (int *)malloc(sizeof(int) * n);
// 		for (i = 0; i < n; i++)
// 			prufer[i] = prufer_1indexed[i] - 1;
// 	}
// 	else
// 	{
// 		n = argc - 1;
// 		prufer = (int *)malloc(sizeof(int) * n);
// 		for (i = 0; i < n; i++)
// 			prufer[i] = atoi(argv[i + 1]) - 1;
// 	}
// 	vertices = n + 2;
// 	degrees = count_degrees(prufer, n);

// 	for (i = 0; i < vertices; i++)
// 	{
// 		printf("%d", degrees[i]);
// 		if (i != vertices - 1)
// 			printf(" ");
// 	}
// 	printf("\n");

// 	free(degrees);
// 	free(prufer);
// 	return (0);
// }
