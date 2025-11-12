#include "genome.h"

static void 	logger(Extremity_ctx *ctx, int i, int *Min, int *Max, int *min, int *max, Stack_int *stack_1, Stack_int *stack_2)
{
	int n_cent;

	n_cent = ctx->n_cent;
	printf("===== LOGGER =====\n\n");
	printf("i: %d, n: %d, n_cent: %d\n", i, ctx->n, ctx->n_cent);
	printf("Min: ");
	print_array_int(Min, n_cent, 2);
	printf("Max: ");
	print_array_int(Max, n_cent, 2);
	printf("min: ");
	print_array_int(min, n_cent, 2);
	printf("max: ");
	print_array_int(max, n_cent, 2);
	printf("stack_1: ");
	print_stack(stack_1);
	printf("stack_2: ");
	print_stack(stack_2);
	printf("\n========\n\n");
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

void	find_components_1(Extremity_ctx *ctx, int *maxes, int *mins)
{
	Stack_int *stack_1, *stack_2;
	int *Min, *Max, *min, *max;
	int *perm_cent, *sigma_cent;
	int i, s, pi, n, n_cent;
	n = ctx->n;
	n_cent = ctx->n_cent;
	perm_cent = ctx->perm_cent;
	sigma_cent = ctx->sigma_cent;
	print_array_int(sigma_cent, n_cent, 2);

	Min = (int *)xcalloc(n_cent, sizeof(int));
	Max = (int *)xcalloc(n_cent, sizeof(int));
	min = (int *)xcalloc(n_cent, sizeof(int));
	max = (int *)xcalloc(n_cent, sizeof(int));
	stack_1 = stack_2 = NULL;
	if (!Min || !Max || !min || !max)
		return ;
	printf("allocated arrays.\n");
	for (i = 0; i < n_cent; i++)
	{
		Min[i] = n + 1;
		Max[i] = 0;
		min[i] = n + 1;
		max[i] = 0;
		push_stack(&stack_1, i);
		push_stack(&stack_2, i);
		while (perm_cent[i] != n + 1)
		{
			printf("i: %d, perm_cent[i]: %d\n", i, perm_cent[i]);
			printf("update minima and maxima.\n");
			pi = perm_cent[i];
			update_stack(Min, stack_1, i, pi, min_int);
			update_stack(Max, stack_1, i, pi, max_int);
			update_stack(min, stack_2, i, pi, min_int);
			update_stack(max, stack_2, i, pi, max_int);

			logger(ctx, i, Min, Max, min, max, stack_1, stack_2);

			printf("Find components of types 1 and 3\n");
			s = peek_stack(stack_1);
			while (perm_cent[s] > perm_cent[i] || maxes[s] < perm_cent[i])
			{
				printf("while 1\n");
				pop_stack(&stack_1);
				update_stack(Min, stack_1, i, pi, min_int);
				update_stack(Max, stack_1, i, pi, max_int);
				s = peek_stack(stack_1);
			}
			if (sigma_cent[i] == 1 &&
				maxes[i] == maxes[s] &&
				((perm_cent[s] != 0 && Max[s] - Min[s] == i - s) ||
				(perm_cent[s] == 0 && Max[s] - Min[s] == i - s - 1 &&
				get_ext_by_perm_index(ctx, ctx->exts, Min[s])->reality == ctx->ext_l)))
			{
				printf("report_component type 1\n");
				report_component(ctx, get_ext_by_perm_index(ctx, ctx->exts, s), get_ext_by_perm_index(ctx, ctx->exts, i), 1);
			}
			// Find components of type 7
			printf("Find components of type 7\n");
			logger(ctx, i, Min, Max, min, max, stack_1, stack_2);
			s = peek_stack(stack_2);
			while ((perm_cent[s] < perm_cent[i] || mins[s] > perm_cent[s]) && perm_cent[s] > 0)
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
				logger(ctx, i, Min, Max, min, max, stack_1, stack_2);
			}
			if (sigma_cent[i] == -1 &&
				mins[i] == mins[s] &&
				perm_cent[s] == 0 &&
				max[s] - min[s] == i - s - 1 &&
				max[s]) // && // is at a right chromosome end in B)// all elements from s to i are on the same chromosome in B
			{
				// report the component (s, ..., i)
				printf("report_component type 7\n");
				report_component(ctx, get_ext_by_perm_index(ctx, ctx->exts, s), get_ext_by_perm_index(ctx, ctx->exts, i), 7);
			}
			printf("update stacks\n");
			if (sigma_cent[i] == 1)
				push_stack(&stack_1, i);
			else
				push_stack(&stack_2, i);
			i++;
		}

		s = peek_stack(stack_1);
		while (perm_cent[s] != 0)
		{
			pop_stack(&stack_1);
			update_stack(Min, stack_1, i, pi, min_int);
			update_stack(Max, stack_1, i, pi, max_int);
			s = peek_stack(stack_1);
		}
		if (sigma_cent[s + 1] == 1 &&
			Max[s] - Min[s] == i - s - 2 &&
			Min[s] && // is at a left chromosome end in B
			Max[s] && // is at a right chromosome end in B
			1 == 1)
			// all elements from s to i are on the same chromosome in B
			// this chromosome is not a chain of shorter components
		{
			// report the component (s, ..., i)
			printf("report_component type 4\n");
			report_component(ctx, get_ext_by_perm_index(ctx, ctx->exts, s), get_ext_by_perm_index(ctx, ctx->exts, i), 4);
		}
	}
}
