#include "genome.h"

typedef struct
{
	int *id;
	int *sign;
}		Centinel;

static void 	logger(Extremity_ctx *ctx, int i, Centinel *Min, Centinel *Max, Centinel *min, Centinel *max, Stack_int *stack_1, Stack_int *stack_2, int *cmp_ids)
{
	int n_sent;

	n_sent = ctx->n_sent;
	printf("===== LOGGER =====\n\n");
	printf("i: %d, n: %d, n_sent: %d\n", i, ctx->n, ctx->n_sent);
	printf("sgn: ");
	print_array_int(ctx->sigma_sent, n_sent, 2);
	printf("ids: ");
	print_array_int(ctx->perm_sent, n_sent, 2);
	printf("Min: ");
	print_array_int(Min->id, n_sent, 2);
	printf("Max: ");
	print_array_int(Max->id, n_sent, 2);
	printf("min: ");
	print_array_int(min->id, n_sent, 2);
	printf("max: ");
	print_array_int(max->id, n_sent, 2);
	printf("stack_1: ");
	print_stack(stack_1);
	printf("stack_2: ");
	print_stack(stack_2);
	printf("cmp: ");
	print_array_int(cmp_ids, n_sent, 2);
	printf("\n========\n\n");
}

void 	update_stack(Centinel *array, Stack_int *stack, int i, int pi, int si, int (*f)(int, int))
{
	array->id[i] = pi;
	array->sign[i] = si;
	array->id[peek_stack(stack)] = f(array->id[peek_stack(stack)], pi);
	array->sign[peek_stack(stack)] = f(array->sign[peek_stack(stack)], si);
}

void	report_component(Components *cmps, int s, int i)
{
	int *starts, *ends;

	starts = cmps->starts;
	ends = cmps->ends;
	if (ends[s] == -1 || i < ends[s])
		ends[s] = i;
	if (starts[i] == -1 || starts[i] < s)
		starts[i] = s;
}

void	find_components_1(Extremity_ctx *ctx, int *maxes, int *mins, Components *cmps)
{
	Stack_int *stack_1, *stack_2, *tmp;
	// int *Min, *Max, *min, *max;
	Centinel Min, Max, min, max;
	int *perm_sent, *sigma_sent, *cmp_ids;
	int i, s, pi, si, n, n_sent, cmp_id;
	n = ctx->n;
	n_sent = ctx->n_sent;
	perm_sent = ctx->perm_sent;
	sigma_sent = ctx->sigma_sent;

	Min.id = (int *)xcalloc(n_sent, sizeof(int));
	Max.id = (int *)xcalloc(n_sent, sizeof(int));
	min.id = (int *)xcalloc(n_sent, sizeof(int));
	max.id = (int *)xcalloc(n_sent, sizeof(int));
	Min.sign = (int *)xcalloc(n_sent, sizeof(int));
	Max.sign = (int *)xcalloc(n_sent, sizeof(int));
	min.sign = (int *)xcalloc(n_sent, sizeof(int));
	max.sign = (int *)xcalloc(n_sent, sizeof(int));
	cmp_ids = (int *)xcalloc(n_sent, sizeof(int));

	stack_1 = NULL;
	stack_2 = NULL;
	if (!Min.id || !Max.id || !min.id || !max.id ||
		!Min.sign || !Max.sign || !min.sign || !max.sign)
		return ;
	cmp_id = 0;
	printf("allocated arrays.\n");
	for (i = 0; i < n_sent; i++)
	{
		Min.id[i] = n;Min.sign[i] = 1;
		Max.id[i] = 0;Max.sign[i] = 1;
		min.id[i] = n;min.sign[i] = 1;
		max.id[i] = 0;max.sign[i] = 1;
		cmp_id++;
		push_stack(&stack_1, i);
		push_stack(&stack_2, i);
		printf("\n$$$$$$$$$$$$$$$$$$$$$$$$\n\ni: %d, perm_sent[i]: %d\n", i, perm_sent[i]);
		while (perm_sent[i] != n + 1)
		{
			printf("update minima and maxima.\n");
			pi = perm_sent[i];
			si = sigma_sent[i];
			cmp_ids[i] = cmp_id;
			update_stack(&Min, stack_1, i, pi, si, min_int);
			update_stack(&Max, stack_1, i, pi, si, max_int);
			update_stack(&min, stack_2, i, pi, si, min_int);
			update_stack(&max, stack_2, i, pi, si, max_int);

			logger(ctx, i, &Min, &Max, &min, &max, stack_1, stack_2, cmp_ids);

			printf("Find components of types 1 and 3\n");
			s = peek_stack(stack_1);
			printf("s: %d\n", s);
			printf("comparing %d > %d or %d < %d\n", perm_sent[s], perm_sent[i], maxes[s], perm_sent[i]);
			while (perm_sent[s] > perm_sent[i] || maxes[s] < perm_sent[i])
			{
				printf("while 1\n");
				tmp = pop_stack(&stack_1);
				free_stack_node(tmp);
				update_stack(&Min, stack_1, i, pi, si, min_int);
				update_stack(&Max, stack_1, i, pi, si, max_int);
				s = peek_stack(stack_1);
			}
			printf("s: %d, i: %d\n", s, i);
			printf("sigma_sent[%d]: %d\n", i, sigma_sent[i]);
			printf("maxes[%d] == maxes[%d]: %d == %d\n", s, i, maxes[s], maxes[i]);
			printf("Max.id[s] - Min.id[s]: %d\n", Max.id[s] - Min.id[s]);
			printf("get_ext_by_value(ctx, ctx->exts, Min.id[s] * Min.sign[s])->id: %d\n", get_ext_by_value(ctx, ctx->exts, Min.id[s] * Min.sign[s])->id);
			if (sigma_sent[i] == 1 && i != s &&
				maxes[s] == maxes[i] &&
				((perm_sent[s] != 0 && Max.id[s] - Min.id[s] == i - s) ||
				(perm_sent[s] == 0 && Max.id[s] - Min.id[s] == i - s - 1 &&
				get_ext_by_value(ctx, ctx->exts, Min.id[s] * Min.sign[s])->id == 0)))
			{
				printf("report_component type 1\n");
				report_component(cmps, s, i);
			}
			// Find components of type 7
			printf("Find components of type 7\n");
			// logger(ctx, i, &Min, &Max, &min, &max, stack_1, stack_2, cmp_ids);
			s = peek_stack(stack_2);
			while ((perm_sent[s] < perm_sent[i] || mins[s] > perm_sent[s]) && perm_sent[s] > 0)
			{
				tmp = pop_stack(&stack_2);
				free_stack_node(tmp);
				update_stack(&min, stack_2, i, pi, si, min_int);
				update_stack(&max, stack_2, i, pi, si, max_int);
				s = peek_stack(stack_2);
				// logger(ctx, i, &Min, &Max, &min, &max, stack_1, stack_2, cmp_ids);
			}
			if (sigma_sent[i] == -1 && i != s &&
				mins[i] == mins[s] &&
				perm_sent[s] == 0 &&
				max.id[s] - min.id[s] == i - s - 1 &&
				get_ext_by_value(ctx, ctx->exts, max.id[s] * max.sign[s])->reality->id == n + 1 &&
				cmp_ids[s] == cmp_ids[i])// is at a right chromosome end in B)
			{
				// report the component (s, ..., i)
				printf("report_component type 7\n");
				report_component(cmps, s, i);
			}
			printf("update stacks\n");
			if (sigma_sent[i] == 1)
				push_stack(&stack_1, i);
			else
				push_stack(&stack_2, i);
			i++;
		}
		cmp_ids[i] = cmp_id;
		// logger(ctx, i, &Min, &Max, &min, &max, stack_1, stack_2, cmp_ids);
		s = peek_stack(stack_1);
		while (perm_sent[s] != 0)
		{
			printf("clearing stack_1\n");
			tmp = pop_stack(&stack_1);
			// logger(ctx, i, &Min, &Max, &min, &max, stack_1, stack_2, cmp_ids);
			free_stack_node(tmp);
			update_stack(&Min, stack_1, i, pi, si, min_int);
			update_stack(&Max, stack_1, i, pi, si, max_int);
			s = peek_stack(stack_1);
		}
		if (sigma_sent[s + 1] == 1 &&
			Max.id[s] - Min.id[s] == i - s - 2 &&
			get_ext_by_value(ctx, ctx->exts, Min.id[s] * Min.sign[s])->reality->id == 0 && // is at a left chromosome end in B
			get_ext_by_value(ctx, ctx->exts, Max.id[s] * Max.sign[s])->reality->id == n + 1 && // is at a right chromosome end in B
			cmp_ids[s] == cmp_ids[i])
		{
			// report the component (s, ..., i)
			printf("report_component type 4\n");
			report_component(cmps, s, i);
		}
		printf("after a chromosome.\n");
		// logger(ctx, i, &Min, &Max, &min, &max, stack_1, stack_2, cmp_ids);
	}
	free_array_int(Min.id, n_sent);
	free_array_int(Min.sign, n_sent);
	free_array_int(Max.id, n_sent);
	free_array_int(Max.sign, n_sent);
	free_array_int(min.id, n_sent);
	free_array_int(min.sign, n_sent);
	free_array_int(max.id, n_sent);
	free_array_int(max.sign, n_sent);
	free_array_int(cmp_ids, n_sent);
	free_stack(stack_1);
	free_stack(stack_2);
}
