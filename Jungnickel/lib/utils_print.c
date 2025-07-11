#include "lib.h"

static int count_max_digits(int **matrix, int r, int c)
{
	int i, j, max, digit;

	max = 1;
	for (i = 0; i < r; i++)
		for (j = 0; j < c; j++)
		{
			digit = count_digit(matrix[i][j]);
			if (digit > max)
				max = digit;
		}
	return max;
}

void print_matrix_int(int **matrix, int r, int c)
{
	int i;
	int max_width;

	if (!matrix)
	{
		printf("matrix is NULL\n");
		return;
	}
	max_width = count_max_digits(matrix, r, c);
	for (i = 0; i < r; i++)
	{
		if (!matrix[i])
			return;
		print_array_int(matrix[i], c, max_width);
	}
}


/**
 * @param max_width 0, if you wanna disable digit alignment
 */
void print_array_int(int *arr, int n, int max_width)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%*d", max_width, arr[i]);
		printf((i == n - 1) ? "\n" : " ");
	}
}

static int count_max_double_width(double **matrix, int r, int c, int precision)
{
    int i, j, max_int_width, int_width;
    double value;

    max_int_width = 1;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            value = matrix[i][j];
            if (value < 0)
            {
                value = -value;
                int_width = 1;
            }
            else
                int_width = 0;
            if (value < 1.0)
                int_width += 1;  // Just "0" before decimal
            else
                while (value >= 1.0)
                {
                    int_width++;
                    value /= 10.0;
                }
            if (int_width > max_int_width)
                max_int_width = int_width;
        }
    }
    return max_int_width + 1 + precision;
}

void print_matrix_double(double **matrix, int r, int c, int precision)
{
    int i;
    int max_width;

    if (!matrix)
    {
        printf("matrix is NULL\n");
        return;
    }

    if (precision <= 0)
        precision = 3;
    max_width = count_max_double_width(matrix, r, c, precision);
    for (i = 0; i < r; i++)
    {
        if (!matrix[i])
            return;
        print_array_double(matrix[i], c, max_width, precision);
    }
}

void print_array_double(double *arr, int n, int max_width, int precision)
{
    int i;
    char format[20];

    if (precision <= 0)
        precision = 3;
    if (max_width <= 0)
        sprintf(format, "%%.%df", precision);
    else
        sprintf(format, "%%%d.%df", max_width, precision);
    for (i = 0; i < n; i++)
    {
        printf(format, arr[i]);
        printf((i == n - 1) ? "\n" : " ");
    }
}

// void	print_matrix_double(double **matrix, int r, int c)
// {
// 	int i;

// 	for (i = 0; i < r; i++)
// 		print_array_double(matrix[i], c);
// }

// void 	print_array_double(double *arr, int c)
// {
// 	int j;

// 	for (j = 0; j < c; j++)
// 		printf("%.3f%c", arr[j], j == c - 1 ? '\n' : ' ');
// }

void	print_vertex(Vertex *v)
{
	if (!v)
		return ;
	printf("vId: %d", v->id);
	print_edge_list(v->incidence);
}

void	print_vertices(Vertex **vs, int n)
{
	int	i;

	i = 0;
	if (!vs)
		return ;
	while (i < n)
	{
		print_vertex(vs[i]);
		i++;
	}
}

void	print_edge_list(Edge *head)
{
	Edge	*cur;

	cur = head;
	while (cur)
	{
		printf(" -> ");
		printf("%d", cur->to);
		cur = cur->next;
	}
	printf("\n");
}

void 	print_pathnode(PathNode *head)
{
	PathNode	*cur;

	cur = head;
	while (cur)
	{
		printf(" -> ");
		printf("%d", cur->v->id);
		cur = cur->next;
	}
	printf("\n");
}

void print_edgenode(EdgeNode *head)
{
	double cost;

	cost = 0.0;
	while (head)
	{
		printf("%d - %d\n", head->edge->from, head->edge->to);
		cost += head->edge->cost;
		head = head->next;
	}
	if (cost)
		printf("cost was %f\n", cost);
}

void	print_array_char(char **ss, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%s\n", ss[i]);
	}
}

void	print_info()
{
	double used_time;

	proc_end = clock();
	used_time = ((double) (proc_end - proc_start)) / CLOCKS_PER_SEC;
	printf("mem_peak: %d\n", (int)mem_peak);
	printf("remaining mem: %d\n", (int)mem);
	printf("proccess time: %f\n", used_time);
}
