#include "genome.h"

static void 	logger(Extremity_ctx *ctx, int *Min, int *Max, int *min, int *max, Stack_int *stack_1, Stack_int *stack_2)
{
	int n;

	n = ctx->n;
	printf("Min: ");
	print_array_int(Min, n, 2);
	printf("Max: ");
	print_array_int(Max, n, 2);
	printf("min: ");
	print_array_int(min, n, 2);
	printf("max: ");
	print_array_int(max, n, 2);
	print_stack(stack_1);
	print_stack(stack_2);
}

void 	update_stack(int *array, Stack_int *stack, int i, int pi, int (*f)(int, int))
{
	array[i] = pi;
	array[peek_stack(stack)] = f(array[peek_stack(stack)], pi);
}

void	report_component(Extremity_ctx *ctx, Extremity *start, Extremity *end, int type)
{
	Component *comp;

	comp = create_component();
	comp->start = start;
	comp->end = end;
	comp->type = type;
	if (ctx->head)
		ctx->head->prev = comp;
	comp->prev = NULL;
	comp->next = ctx->head;
	ctx->head = comp;
}

void	find_components_1(Extremity_ctx *ctx, int *maxes, int *mins, int n)
{
	Stack_int *stack_1, *stack_2;
	int *Min, *Max, *min, *max;
	int *perm;
	int i, s, pi;

	Min = (int *)xcalloc(n, sizeof(int));
	Max = (int *)xcalloc(n, sizeof(int));
	min = (int *)xcalloc(n, sizeof(int));
	max = (int *)xcalloc(n, sizeof(int));
	stack_1 = stack_2 = NULL;
	perm = ctx->perm;
	if (!Min || !Max || !min || !max)
		return ;
	printf("allocated arrays.\n");
	for (i = 0; i < n; i++)
	{
		Min[i] = n + 1;
		Max[i] = 0;
		min[i] = n + 1;
		max[i] = 0;
		push_stack(&stack_1, i);
		push_stack(&stack_2, i);
		while (perm[i] != n + 1)
		{
			printf("i: %d, perm[i]: %d\n", i, perm[i]);
			printf("update minima and maxima.\n");
			pi = abs(perm[i]);
			update_stack(Min, stack_1, i, pi, min_int);
			update_stack(Max, stack_1, i, pi, max_int);
			update_stack(min, stack_2, i, pi, min_int);
			update_stack(max, stack_2, i, pi, max_int);

			logger(ctx, Min, Max, min, max, stack_1, stack_2);

			printf("Find components of types 1 and 3\n");
			s = peek_stack(stack_1);
			while (perm[s] > perm[i] || maxes[s] < perm[i])
			{
				pop_stack(&stack_1);
				update_stack(Min, stack_1, i, pi, min_int);
				update_stack(Max, stack_1, i, pi, max_int);
				s = peek_stack(stack_1);
			}
			if (perm[i] / pi == 1 &&
				maxes[i] == maxes[s] &&
				((perm[s] != 0 && Max[s] - Min[s] == i - s) ||
				(perm[s] == 0 && Max[s] - Min[s] == i - s - 1 &&
				get_index_of(ctx, Min[s])->reality == ctx->ext_l)))
			{
				printf("report_component type 1\n");
				report_component(ctx, get_index_of(ctx, s), get_index_of(ctx, i), 1);
			}
			// Find components of type 7
			printf("Find components of type 7\n");
			logger(ctx, Min, Max, min, max, stack_1, stack_2);
			s = peek_stack(stack_2);
			while ((perm[s] < perm[i] || mins[s] > perm[s]) && perm[s] > 0)
			{
				if (s == INT_MIN)
				{
					printf("INT_MIN\n");
					break;
				}
				pop_stack(&stack_2);
				update_stack(min, stack_2, i, pi, min_int);
				update_stack(max, stack_2, i, pi, max_int);
				s = peek_stack(stack_2);
				logger(ctx, Min, Max, min, max, stack_1, stack_2);
			}
			if (perm[i] / pi == -1 &&
				mins[i] == mins[s] &&
				perm[s] == 0 &&
				max[s] - min[s] == i - s - 1 &&
				max[s]) // && // is at a right chromosome end in B)
				// all elements from s to i are on the same chromosome in B
			{
				// report the component (s, ..., i)
				printf("report_component type 7\n");
				report_component(ctx, get_index_of(ctx, s), get_index_of(ctx, i), 7);
			}

			printf("update stacks\n");
			if (perm[i] / pi == 1)
				push_stack(&stack_1, i);
			else
				push_stack(&stack_2, i);
			i++;
		}

		s = peek_stack(stack_1);
		while (perm[s] != 0)
		{
			pop_stack(&stack_1);
			update_stack(Min, stack_1, i, pi, min_int);
			update_stack(Max, stack_1, i, pi, max_int);
			s = peek_stack(stack_1);
		}
		if (perm[s + 1] / abs(perm[s + 1]) == 1 &&
			Max[s] - Min[s] == i - s - 2 &&
			Min[s] && // is at a left chromosome end in B
			Max[s] && // is at a right chromosome end in B
			1 == 1)
			// all elements from s to i are on the same chromosome in B
			// this chromosome is not a chain of shorter components
		{
			// report the component (s, ..., i)
			printf("report_component type 4\n");
			report_component(ctx, get_index_of(ctx, s), get_index_of(ctx, i), 4);
		}
	}
}
