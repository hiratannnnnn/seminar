#include "bipartite.h"

int **read_matrix(int *a, int *b, char const *filename)
{
	FILE *fp;
	int **matrix;
	int i, j;

	fp = fopen(filename, "r");
	if (!fp)
		return (NULL);
	if (fscanf(fp, "%d %d", a, b) != 2)
		return (fclose(fp), NULL);
	matrix = generate_matrix_int(*a, *b);
	if (!matrix)
		return (fclose(fp), NULL);
	for (i = 0; i < *a; i++)
	{
		for (j = 0; j < *b; j++)
		{
			if (fscanf(fp, "%d", &matrix[i][j]) != 1)
			{
				free_matrix_int(matrix, i, *b);
				fclose(fp);
				return (NULL);
			}
		}
	}
	fclose(fp);
	return matrix;
}


double **read_double_matrix(int *r, int *c, char const *filename)
{
    FILE *fp;
    double **matrix;
    int i, j;

    fp = fopen(filename, "r");
    if (!fp)
        return NULL;
    if (fscanf(fp, "%d %d", r, c) != 2)
        return (fclose(fp), NULL);
    matrix = generate_matrix_double(*r, *c);
    if (!matrix)
        return (fclose(fp), NULL);
    for (i = 0; i < *r; i++)
    {
        for (j = 0; j < *c; j++)
        {
            if (fscanf(fp, "%lf", &matrix[i][j]) != 1)
            {
                free_matrix_double(matrix, *r, *c);
                fclose(fp);
                return NULL;
            }
        }
    }
    fclose(fp);
    return matrix;
}
