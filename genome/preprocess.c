# include "genome.h"

static void	pop_stack_thres(Stack_int **head, int thres, int sign)
{
	Stack_int *cur;

	cur = *head;
	while (cur)
	{
		if (sign == -1 && cur->nbr < thres)
		{
			cur = pop_stack(head);
			free_stack_node(cur);
		}
		else if (sign == 1 && cur->nbr > thres)
		{
			cur = pop_stack(head);
			free_stack_node(cur);
		}
		else
			break;
		cur = *head;
	}
}

int preprocess(Extremity_ctx *ctx, int *maxes, int *mins)
{
	Stack_int *M_stack, *m_stack;
	int *perm_cent, *sigma_cent;
	int n, n_cent, i, id, prev_id;

	M_stack = create_stack_node((ctx->n) + 1);
	m_stack = create_stack_node(0);
	if (!M_stack || !m_stack)
		return (-1);
	n = ctx->n;
	n_cent = ctx->n_cent;
	perm_cent = ctx->perm_cent;
	sigma_cent = ctx->sigma_cent;
	i = 0;
	while (i < n_cent)
	{
		maxes[i] = n + 1;
		mins[i] = 0;
		i++;
		while (!(perm_cent[i] * sigma_cent[i] != n + 1 ||
				(perm_cent[i] == 0 && sigma_cent[i] == -1)))
		{
			printf("%d\n", i);
			id = perm_cent[i];
			prev_id = perm_cent[i - 1];
			if (prev_id > id)
				push_stack(&M_stack, prev_id);
			else
				pop_stack_thres(&M_stack, id, -1);
			maxes[i] = peek_stack(M_stack);
			if (prev_id < id)
				push_stack(&m_stack, prev_id);
			else
				pop_stack_thres(&m_stack, id, 1);
			mins[i] = peek_stack(m_stack);
			i++;
		}
		maxes[i] = n + 1;
		mins[i] = 0;
		i++;
	}
	free_stack(M_stack);
	free_stack(m_stack);
	return (1);
}
